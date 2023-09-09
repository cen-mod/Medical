//------------------------------------------------------------------------------------------------
enum E_CEN_StateMachine_Event
{
}

//------------------------------------------------------------------------------------------------
class CEN_StateMachine_State : Managed
{
	void OnState(IEntity owner) {};
	void OnStateEntered(IEntity owner) {};
	void OnStateLeaving(IEntity owner) {};
}

//------------------------------------------------------------------------------------------------
class CEN_StateMachine_Transition : Managed
{
	// These variables should be assigned in the ctor
	typename m_tSourceStateName;
	typename m_tTargetStateName;
	
	bool Condition(IEntity owner) { return true; };
	void OnTransition(IEntity owner) {};
}

//------------------------------------------------------------------------------------------------
class CEN_StateMachine_Machine : Managed
{
	// These variables should be assigned in the ctor
	protected float m_fOnStateTimeout = 0;
	
	protected IEntity m_eOwner;
	protected typename m_sCurrentStateName;
	protected CEN_StateMachine_State m_CurrentState;
	protected ref map<typename,ref CEN_StateMachine_State> m_mStates = new map<typename,ref CEN_StateMachine_State>;
	protected ref map<E_CEN_StateMachine_Event,ref map<typename, ref CEN_StateMachine_Transition>> m_mTransitions = new ref map<E_CEN_StateMachine_Event,ref map<typename, ref CEN_StateMachine_Transition>>;
	protected ref array<E_CEN_StateMachine_Event> m_aScheduledEvents;
	protected int m_iNextOnStateTick = 0;
	
	//------------------------------------------------------------------------------------------------
	void CEN_StateMachine_Machine(IEntity owner, CEN_StateMachine_State initialState)
	{
		m_eOwner = owner;
		m_sCurrentStateName = initialState.Type();
		m_CurrentState = initialState;
		AddState(initialState);
		CEN_StateMachine_Clockwork.GetInstance().AddMachine(this);
	}
	
	//------------------------------------------------------------------------------------------------
	void ~CEN_StateMachine_Machine()
	{
		CEN_StateMachine_Clockwork.GetInstance().RemoveMachine(this);
	}
	
	//------------------------------------------------------------------------------------------------
	void AddState(CEN_StateMachine_State state)
	{
		m_mStates.Set(state.Type(), state);
	}
	
	//------------------------------------------------------------------------------------------------
	void AddTransition(E_CEN_StateMachine_Event eventId, CEN_StateMachine_Transition transition)
	{
		typename sourceStateName = transition.m_tSourceStateName;
		
		map<typename, ref CEN_StateMachine_Transition> transitions;
		if (!m_mTransitions.Find(eventId, transitions))
		{
			transitions = new map<typename,ref CEN_StateMachine_Transition>;
			transitions.Set(sourceStateName, transition);
			m_mTransitions.Set(eventId, transitions);
		}
		else
		{
			transitions.Set(sourceStateName, transition);
		};
	}
	
	//------------------------------------------------------------------------------------------------
	typename GetCurrentStateName()
	{
		return m_sCurrentStateName;
	}
	
	//------------------------------------------------------------------------------------------------
	void ScheduleEvent(E_CEN_StateMachine_Event eventId)
	{
		m_aScheduledEvents.Insert(eventId);
	}
	
	//------------------------------------------------------------------------------------------------
	void Tick()
	{
		int curTick = System.GetTickCount();
		if (curTick >= m_iNextOnStateTick)
		{
			m_CurrentState.OnState(m_eOwner);
			m_iNextOnStateTick = curTick + m_fOnStateTimeout * 1000;
		};
		
		if (m_aScheduledEvents.IsEmpty())
			return;
		
		// Execute next scheduled event
		E_CEN_StateMachine_Event eventId = m_aScheduledEvents[0];
		m_aScheduledEvents.Remove(0);
		
		map<typename, ref CEN_StateMachine_Transition> transitions;
		if (!m_mTransitions.Find(eventId, transitions))
			return;
		
		CEN_StateMachine_Transition transition;
		if (!transitions.Find(m_sCurrentStateName, transition))
			return;
		
		if (!transition.Condition(m_eOwner))
			return;
		
		if (!m_mStates.Find(m_sCurrentStateName, m_CurrentState))
			return;
		
		m_CurrentState.OnStateLeaving(m_eOwner);
		transition.OnTransition(m_eOwner);
		
		// Update to new state
		m_sCurrentStateName = transition.m_tTargetStateName;
		if (!m_mStates.Find(m_sCurrentStateName, m_CurrentState))
			return;
		
		m_CurrentState.OnStateEntered(m_eOwner);		
	}
}
