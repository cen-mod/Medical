//------------------------------------------------------------------------------------------------
modded class SCR_BaseGameMode : BaseGameMode
{
	protected ref CEN_StateMachine_Clockwork m_CEN_StateMachine_clockwork;
	
	//------------------------------------------------------------------------------------------------
	void SCR_BaseGameMode(IEntitySource src, IEntity parent)
	{
		if (!GetGame().InPlayMode())
			return;
		
		m_CEN_StateMachine_clockwork = CEN_StateMachine_Clockwork.GetInstance();
	}
	
	//------------------------------------------------------------------------------------------------
	override void EOnFrame(IEntity owner, float timeSlice)
	{
		super.EOnFrame(owner, timeSlice);
		m_CEN_StateMachine_clockwork.Tick();
	}
}
