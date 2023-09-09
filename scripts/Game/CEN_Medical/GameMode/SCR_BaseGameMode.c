//------------------------------------------------------------------------------------------------
modded class SCR_BaseGameMode : BaseGameMode
{
	[Attribute("10", UIWidgets.EditBox, desc: "Number of state machine ticks handled in one frame", category: "CEN")]
	protected int m_iCEN_StateMachine_TicksPerFrame;
	
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
		
		for (int i = 0; i < m_iCEN_StateMachine_TicksPerFrame; i++)
		{
			m_CEN_StateMachine_clockwork.Tick();
		};
	}
}
