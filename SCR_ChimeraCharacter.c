 modded class SCR_ChimeraCharacter : ChimeraCharacter
{
	protected float m_fCEN_Medical_lastUpdateTime = 0;
	protected float m_fCEN_Medical_lastMomentValuesSynced =0;

	//------------------------------------------------------------------------------------------------
    float CEN_Medical_getLastUpdateTime()
    {
     	return m_fCEN_Medical_lastUpdateTime;
    }

	//------------------------------------------------------------------------------------------------
    void CEN_Medical_updateLastUpdateTime()
    {
     	m_fCEN_Medical_lastUpdateTime = GetGame().GetWorld().GetWorldTime();
    }
	
	//------------------------------------------------------------------------------------------------
	float CEN_Medical_getlastTimeValuesSynced()
	{
		return m_fCEN_Medical_lastMomentValuesSynced;
	}
		
	//------------------------------------------------------------------------------------------------
	void CEN_Medical_updatelastTimeValuesSynced()
	{
		m_fCEN_Medical_lastMomentValuesSynced = GetGame().GetWorld().GetWorldTime();
	}
}
