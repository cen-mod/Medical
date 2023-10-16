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
	[RplProp()]
	protected int m_iHeartRate = GetDefaultHeartRate();
	[RplProp()]
	protected float m_fPeriph_res;
	
	protected float m_fBloodVolume4;
	protected float m_fBloodVolume3;
	protected float m_fBloodVolume2;
	protected float m_fBloodVolume1;
	protected float m_fBloodVolumeFatal;
	protected int m_idefHeartRate;
	protected float m_fdefBloodVolume;
	//------------------------------------------------------------------------------------------------
	float GetBloodVolume(SCR_ChimeraCharacter unit )
	{	
		SCR_CharacterDamageManagerComponent damageManagerComponent = SCR_CharacterDamageManagerComponent.Cast(unit.FindComponent(SCR_CharacterDamageManagerComponent));
		SCR_CharacterBloodHitZone bloodvolume = SCR_CharacterBloodHitZone.Cast( damageManagerComponent.GetHitZoneByName("Blood"));
		float m_fbloodVolume = bloodvolume.GetHealth();
		return m_fbloodVolume;
	}
	//------------------------------------------------------------------------------------------------
	float GetDefaultBloodVolume(SCR_ChimeraCharacter unit)
	{	
		SCR_CharacterDamageManagerComponent damageManagerComponent = SCR_CharacterDamageManagerComponent.Cast(unit.FindComponent(SCR_CharacterDamageManagerComponent));
		SCR_CharacterBloodHitZone bloodvolume = SCR_CharacterBloodHitZone.Cast( damageManagerComponent.GetHitZoneByName("Blood"));
		float m_fBloodVolumedef = bloodvolume.GetMaxHealth();
		return m_fBloodVolumedef;
	}
	
	//------------------------------------------------------------------------------------------------
	int GetHemorrhageClass()
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
	
	//------------------------------------------------------------------------------------------------
	int GetFatalBloodVolume()
	{
		m_fBloodVolumeFatal = m_pBloodHitZone.GetDamageStateThreshold(CEN_Medical_ECharacterBloodState.BLOOD_VOLUME_FATAL);
		if (m_pBloodHitZone.GetHealthScaled() < m_fBloodVolumeFatal)
		{
			return CEN_Medical_ECharacterBloodState.BLOOD_VOLUME_FATAL;
		}
		else
		{
			return GetHemorrhageClass();
		}
		
	}
	
	//------------------------------------------------------------------------------------------------	
	int GetDefaultHeartRate()
	{	
		protected int Min = 60;
		protected int Max = 80;
		Math.Randomize(-1);
		m_idefHeartRate = Math.RandomIntInclusive(Min, Max);
		return m_idefHeartRate;
	}
	
	//------------------------------------------------------------------------------------------------
	
	float GetPeripheralResistance()
	{
		
	}
	
	//------------------------------------------------------------------------------------------------
	/*int PeripheralResistanceAdjustment()
	{
		protected int m_iperipheralResistanceAdjustments = 0;
		
	}
	
	//------------------------------------------------------------------------------------------------
	
	/* void UpdateHeartRate()
	{	
		protected bool m_fsyncValues = SyncValues(SCR_ChimeraCharacter unit);
		protected int m_ihrChange;
		protected int m_itargetHR;
		protected int m_ibloodVolume = GetHemorrhageClass()
		if (GetIsUnconscious() == true)  // mit CRDC arrest ersetzten
		{
			if(m_iHeartRate == 0)
			{
				m_fsyncValues = true;
			}
			if(m_iHeartRate != 0)
			{
				m_fsyncValues = true;
				m_iHeartRate = 0;
			}
		}
		else
		{
			m_ihrChange = 0;
			m_itargetHR = 0;
			if ( m_ibloodVolume = BLOOD_VOLUME_CLASS_4_HEMORRHAGE)
			{
			
			}
		
		}
		Replication.BumpMe();
	}
	*/
	//------------------------------------------------------------------------------------------------
	bool SyncValues(SCR_ChimeraCharacter unit)
	{	
		SCR_ChimeraCharacter  character = SCR_ChimeraCharacter.Cast(unit.FindComponent(SCR_ChimeraCharacter));
		protected float m_flastTimeValuesSynced = character.CEN_Medical_getlastTimeValuesSynced();
		protected float m_fmissionTime = GetGame().GetWorld().GetWorldTime();
		protected bool m_fsyncValues = m_fmissionTime - m_flastTimeValuesSynced >= 10 + Math.Floor(Math.RandomFloat(0, 10));
		return m_fsyncValues;
	}
	int GetBloodPressure()
	{
	
	}
	
	//------------------------------------------------------------------------------------------------
	float GetCardiacOutput(SCR_ChimeraCharacter unit)
	{	
		m_fdefBloodVolume = GetDefaultBloodVolume(unit);
		protected float m_fVentrileStroke = 0.095;
		protected int m_ibloodVolumeRatio = GetBloodVolume(unit) / m_fdefBloodVolume ;
		protected float m_fentering = Math.Map(m_ibloodVolumeRatio, 0.5, 1, 0, 1);
		protected float m_fcardiacOutput = (m_fentering * m_fVentrileStroke) * m_iHeartRate / 60;
		if (m_fcardiacOutput > 0)
		{
			m_fcardiacOutput = 0;
		}
		return m_fcardiacOutput;
		
	}
	
};
