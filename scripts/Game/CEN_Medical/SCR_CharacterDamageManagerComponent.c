enum CEN_Medical_ECharacterBloodState : EDamageState
{
	BLOOD_VOLUME_CLASS_1_HEMORRHAGE = 3,
	BLOOD_VOLUME_CLASS_2_HEMORRHAGE = 4,
	BLOOD_VOLUME_CLASS_3_HEMORRHAGE = 5,
	BLOOD_VOLUME_CLASS_4_HEMORRHAGE,
	BLOOD_VOLUME_FATAL
};

//------------------------------------------------------------------------------------------------
 modded class SCR_CharacterDamageManagerComponent  : ScriptedDamageManagerComponent
{
	protected float m_fBloodVolume4;
	protected float m_fBloodVolume3;
	protected float m_fBloodVolume2;
	protected float m_fBloodVolume1;
	protected float m_fBloodVolumeFatal;
	//------------------------------------------------------------------------------------------------
	float GetBloodVolume(SCR_ChimeraCharacter unit )
	{	
		SCR_CharacterDamageManagerComponent damageManagerComponent = SCR_CharacterDamageManagerComponent.Cast(unit.FindComponent(SCR_CharacterDamageManagerComponent));
		SCR_CharacterBloodHitZone bloodvolume = SCR_CharacterBloodHitZone.Cast( damageManagerComponent.GetHitZoneByName("Blood"));
		float m_fbloodVolume = bloodvolume.GetHealth();
		return m_fbloodVolume;
	}
	//------------------------------------------------------------------------------------------------
	int GetHemorrhageClass(SCR_ChimeraCharacter unit)
	{
		m_fBloodVolume1 = m_pBloodHitZone.GetDamageStateThreshold(CEN_Medical_ECharacterBloodState.BLOOD_VOLUME_CLASS_1_HEMORRHAGE);
		m_fBloodVolume2 = m_pBloodHitZone.GetDamageStateThreshold(CEN_Medical_ECharacterBloodState.BLOOD_VOLUME_CLASS_2_HEMORRHAGE);
		m_fBloodVolume3 = m_pBloodHitZone.GetDamageStateThreshold(CEN_Medical_ECharacterBloodState.BLOOD_VOLUME_CLASS_3_HEMORRHAGE);
		m_fBloodVolume4 = m_pBloodHitZone.GetDamageStateThreshold(CEN_Medical_ECharacterBloodState.BLOOD_VOLUME_CLASS_4_HEMORRHAGE);
		
		if(m_pBloodHitZone.GetHealthScaled() < m_fBloodVolume4 )
		{
			return CEN_Medical_ECharacterBloodState.BLOOD_VOLUME_CLASS_4_HEMORRHAGE;
		}
		else if(m_pBloodHitZone.GetHealthScaled() < m_fBloodVolume3 )
			{
				return CEN_Medical_ECharacterBloodState.BLOOD_VOLUME_CLASS_3_HEMORRHAGE;
			}
		else if(m_pBloodHitZone.GetHealthScaled() < m_fBloodVolume2 )
			{
				return CEN_Medical_ECharacterBloodState.BLOOD_VOLUME_CLASS_2_HEMORRHAGE;
			}
		else if(m_pBloodHitZone.GetHealthScaled() < m_fBloodVolume1 )
			{
				return CEN_Medical_ECharacterBloodState.BLOOD_VOLUME_CLASS_1_HEMORRHAGE;
			}
		else 
			{
				return -1;
			}
	}
	
};
