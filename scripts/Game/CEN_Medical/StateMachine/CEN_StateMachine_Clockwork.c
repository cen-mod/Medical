//------------------------------------------------------------------------------------------------
class CEN_StateMachine_Clockwork : Managed
{
	protected static ref CEN_StateMachine_Clockwork m_Instance = CEN_StateMachine_Clockwork();
	protected ref array<CEN_StateMachine_Machine> m_aMachines = {};
	protected ref array<CEN_StateMachine_Machine> m_aMachinesUpdated = {};
	protected bool m_bMachinesListModified = false;
	protected int m_iCurrentMachine = 0;
	protected int m_iMachineCount = 0;
	
	//------------------------------------------------------------------------------------------------
	private void CEN_StateMachine_Clockwork()
	{
	}
	
	//------------------------------------------------------------------------------------------------
	static CEN_StateMachine_Clockwork GetInstance()
	{
		return m_Instance;
	}
	
	//------------------------------------------------------------------------------------------------
	void Tick()
	{
		if (m_iCurrentMachine >= m_iMachineCount)
		{
			// Update list of machines
			if (m_bMachinesListModified)
			{
				m_aMachines.Copy(m_aMachinesUpdated);
				m_iMachineCount = m_aMachines.Count();
				m_bMachinesListModified = false;
			};
			
			m_iCurrentMachine = 0;
			
		};
		
		CEN_StateMachine_Machine machine = m_aMachines[m_iCurrentMachine];
		if (machine)
		{
			machine.Tick();
		}
		else
		{
			RemoveMachine(machine);
		};
				
		m_iCurrentMachine++;
	}
	
	//------------------------------------------------------------------------------------------------
	void AddMachine(CEN_StateMachine_Machine machine)
	{
		m_aMachinesUpdated.Insert(machine);
		m_bMachinesListModified = true;
	}
	
	//------------------------------------------------------------------------------------------------
	void RemoveMachine(CEN_StateMachine_Machine machine)
	{
		m_aMachinesUpdated.RemoveItem(machine);
		m_bMachinesListModified = true;
	}
}
