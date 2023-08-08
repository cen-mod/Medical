modded class SCR_CharacterDamageManagerComponent : ScriptedDamageManagerComponent
{
	protected CEN_Medical_PainHitZone m_CEN_Medical_pPainHitZone;
	protected float m_CEN_Medical_fModeratePainThreshold;
	protected float m_CEN_Medical_fSeriousPainThreshold;

	//-----------------------------------------------------------------------------------------------------------
	void CEN_Medical_SetPainHitZone(HitZone hitzone)
	{
		m_CEN_Medical_pPainHitZone = CEN_Medical_PainHitZone.Cast(hitzone);
		m_CEN_Medical_fModeratePainThreshold = m_CEN_Medical_pPainHitZone.GetDamageStateThreshold(ECharacterHealthState.MODERATE);
		m_CEN_Medical_fSeriousPainThreshold = m_CEN_Medical_pPainHitZone.GetDamageStateThreshold(ECharacterHealthState.SERIOUS);
	}

	//-----------------------------------------------------------------------------------------------------------
	HitZone CEN_Medical_GetPainHitZone()
	{
		return m_CEN_Medical_pPainHitZone;
	}
	
	//-----------------------------------------------------------------------------------------------------------
	bool CEN_Medical_IsInPain()
	{
		return m_CEN_Medical_pPainHitZone.GetHealthScaled() <= m_CEN_Medical_fModeratePainThreshold;
	}
	
	float CEN_Medical_GetPainIntensity()
	{
		float scaledHealth = Math.Clamp(m_CEN_Medical_pPainHitZone.GetHealthScaled(), m_CEN_Medical_fSeriousPainThreshold, 1);
		
		if (scaledHealth > m_CEN_Medical_fModeratePainThreshold)
		{
			return 0;
		}
		else
		{
			return Math.InverseLerp(1, m_CEN_Medical_fSeriousPainThreshold, scaledHealth);
		};
	}
}