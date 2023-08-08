modded class SCR_CharacterDamageManagerComponent : ScriptedDamageManagerComponent
{
	protected CEN_Medical_PainHitZone m_CEN_Medical_pPainHitZone;

	//-----------------------------------------------------------------------------------------------------------
	void CEN_Medical_SetPainHitZone(HitZone hitzone)
	{
		m_CEN_Medical_pPainHitZone = CEN_Medical_PainHitZone.Cast(hitzone);
	}

	//-----------------------------------------------------------------------------------------------------------
	HitZone CEN_Medical_GetPainHitZone()
	{
		return m_CEN_Medical_pPainHitZone;
	}
	
	//-----------------------------------------------------------------------------------------------------------
	bool CEN_Medical_IsInPain()
	{
		return m_CEN_Medical_pPainHitZone.GetHealthScaled() <= m_CEN_Medical_pPainHitZone.GetDamageStateThreshold(ECharacterHealthState.MODERATE);
	}
}