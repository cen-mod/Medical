class CEN_Medical_PainScreenEffect : SCR_BaseScreenEffect
{
	// Play Animation of CreateEffectOverTime()
	protected const int   BLEEDING_REPEAT_DELAY 						= 1000;
	protected const float BLEEDINGEFFECT_OPACITY_FADEOUT_1_DURATION 	= 0.2;
	protected const float BLEEDINGEFFECT_PROGRESSION_FADEOUT_1_DURATION = 0.2;
	protected const float BLEEDINGEFFECT_OPACITY_FADEOUT_2_DURATION 	= 0.3;
	protected const float BLEEDINGEFFECT_PROGRESSION_FADEOUT_2_DURATION = 3;
	protected const float BLEEDINGEFFECT_OPACITY_FADEIN_1_DURATION		= 1;
	protected const float BLEEDINGEFFECT_PROGRESSION_FADEIN_1_DURATION  = 4.5;
	
	// Play Animation of BlackoutEffect()
	protected const float BLACKOUT_OPACITY_MULTIPLIER					= 0.20;
	
	//Saturation
	private static float s_fSaturation;
		
	// Widgets
	protected ImageWidget 							m_wWhiteFlash;
	private int m_iEffectNo 						= 1;
	
	// Character
	protected SCR_CharacterDamageManagerComponent	m_pDamageManager;
	protected CEN_Medical_PainHitZone				m_pPainHZ;
	private bool m_bLocalPlayerOutsideCharacter;
	protected ChimeraCharacter						m_pCharacterEntity;

	protected bool m_bPainEffect;
	protected bool m_bIsInPain;

	
	//------------------------------------------------------------------------------------------------
	override void DisplayStartDraw(IEntity owner)
	{
		m_wWhiteFlash = ImageWidget.Cast(m_wRoot.FindAnyWidget("CEN_Medical_WhiteFlash"));
	}	
	
	//------------------------------------------------------------------------------------------------
 	override void DisplayControlledEntityChanged(IEntity from, IEntity to)
	{
		ClearEffects();
		
		m_pCharacterEntity = ChimeraCharacter.Cast(to);
		if (!m_pCharacterEntity)
			return;
		
		m_pDamageManager = SCR_CharacterDamageManagerComponent.Cast(m_pCharacterEntity.GetDamageManager());
		if (!m_pDamageManager)
			return;

		// define hitzones for later getting
		m_pPainHZ = CEN_Medical_PainHitZone.Cast(m_pDamageManager.CEN_Medical_GetPainHitZone());
		
		// Keep track of changes in pain
		m_pPainHZ.GetOnDamageStateChanged().Insert(OnPainStateChanged);
		
		// In case player started bleeding before invokers were established, check if already bleeding
		if (m_pDamageManager.CEN_Medical_IsInPain())
			OnPainStateChanged(m_pPainHZ);
	}

	//------------------------------------------------------------------------------------------------
	void OnPainStateChanged(ScriptedHitZone hitZone)
	{
		m_bIsInPain = m_pDamageManager.CEN_Medical_IsInPain();
		if (m_bPainEffect)
		{
			if (!m_bIsInPain || m_pDamageManager.GetState() == EDamageState.DESTROYED)
			{
				ClearEffectOverTime(false);
				GetGame().GetCallqueue().Remove(CreateEffectOverTime);
				GetGame().GetCallqueue().Remove(ClearEffectOverTime);
				m_bPainEffect = false;
			};
		}
		else
		{
			if (m_bIsInPain && m_pDamageManager.GetState() != EDamageState.DESTROYED)
			{
				CreateEffectOverTime(true);
				m_bPainEffect = m_bIsInPain;
			};
		};
	}
	
	//------------------------------------------------------------------------------------------------
	override void UpdateEffect(float timeSlice, bool playerOutsideCharacter)
	{
		m_bLocalPlayerOutsideCharacter = playerOutsideCharacter;
	}
	
	//------------------------------------------------------------------------------------------------
	void CreateEffectOverTime(bool repeat)
	{
		if (!m_wWhiteFlash || !m_pPainHZ)
			return;
		
		float effectStrength = 0;
		
		// Pain can only be fealt when conscious
		if (!m_pDamageManager.GetIsUnconscious())
			effectStrength = m_pDamageManager.CEN_Medical_GetPainIntensity();
				
		m_wWhiteFlash.SetSaturation(1);
		
		if (m_iEffectNo == 1)
		{
			AnimateWidget.Opacity(m_wWhiteFlash, effectStrength, BLEEDINGEFFECT_OPACITY_FADEIN_1_DURATION);
			AnimateWidget.AlphaMask(m_wWhiteFlash, effectStrength * 0.5, BLEEDINGEFFECT_PROGRESSION_FADEIN_1_DURATION);
		}
		else if (m_iEffectNo == 2)
		{
			AnimateWidget.Opacity(m_wWhiteFlash, 0, BLEEDINGEFFECT_OPACITY_FADEOUT_2_DURATION);
			AnimateWidget.AlphaMask(m_wWhiteFlash, 0, BLEEDINGEFFECT_PROGRESSION_FADEOUT_2_DURATION);
		}

		GetGame().GetCallqueue().CallLater(ClearEffectOverTime, 1000, false, repeat, m_iEffectNo);
	}

	//------------------------------------------------------------------------------------------------
	void ClearEffectOverTime(bool repeat)
	{
		if (m_iEffectNo == 1)
			m_iEffectNo = 2;
		else
			m_iEffectNo = 1;

		AnimateWidget.Opacity(m_wWhiteFlash, 0, BLEEDINGEFFECT_PROGRESSION_FADEOUT_1_DURATION);
		AnimateWidget.AlphaMask(m_wWhiteFlash, 0, BLEEDINGEFFECT_OPACITY_FADEOUT_1_DURATION);
		
		if (repeat && m_bPainEffect)
			GetGame().GetCallqueue().CallLater(CreateEffectOverTime, BLEEDING_REPEAT_DELAY, false, repeat);
	}

	//------------------------------------------------------------------------------------------------
	protected override void ClearEffects()
	{
		m_bPainEffect = 0;
		
		if (m_wWhiteFlash)
		{
			AnimateWidget.StopAllAnimations(m_wWhiteFlash);
			m_wWhiteFlash.SetOpacity(0);
			m_wWhiteFlash.SetMaskProgress(0);
		};
		
		GetGame().GetCallqueue().Remove(CreateEffectOverTime);
		GetGame().GetCallqueue().Remove(ClearEffectOverTime);
		
		if (!m_pDamageManager)
			return;

		m_pPainHZ.GetOnDamageStateChanged().Remove(OnPainStateChanged);
	}
	
	//------------------------------------------------------------------------------------------------
	override event void DisplayStopDraw(IEntity owner)
	{
		if (GetGame().GetHUDManager())
			GetGame().GetHUDManager().GetSceneBrightnessChangedInvoker().Remove(UpdateOpacity);
	}
};