//! Morphine effect
[BaseContainerProps()]
class CEN_Medical_ConsumableMorphine : SCR_ConsumableEffectHealthItems
{
	//------------------------------------------------------------------------------------------------
	override void ApplyEffect(notnull IEntity target, notnull IEntity user, IEntity item, SCR_ConsumableEffectAnimationParameters animParams)
	{
		super.ApplyEffect(target, user, item, animParams);

		ChimeraCharacter char = ChimeraCharacter.Cast(target);
		if (!char)
			return;
		
		SCR_CharacterDamageManagerComponent damageMgr = SCR_CharacterDamageManagerComponent.Cast(char.GetDamageManager());
		if (!damageMgr)
			return;
		
		HitZone painHZ = damageMgr.CEN_Medical_GetPainHitZone();
		if (!painHZ)
			return;
		
		painHZ.SetHealth(painHZ.GetMaxHealth());
	}

	//------------------------------------------------------------------------------------------------
	override bool CanApplyEffect(notnull IEntity target, notnull IEntity user, out SCR_EConsumableFailReason failReason)
	{
		ChimeraCharacter char = ChimeraCharacter.Cast(target);
		if (!char)
			return false;
		
		SCR_CharacterDamageManagerComponent damageMgr = SCR_CharacterDamageManagerComponent.Cast(char.GetDamageManager());
		if (!damageMgr)
			return false;
		
		return damageMgr.CEN_Medical_IsInPain();
	}
	
	//------------------------------------------------------------------------------------------------
	override bool CanApplyEffectToHZ(notnull IEntity target, notnull IEntity user, ECharacterHitZoneGroup group, out SCR_EConsumableFailReason failReason = SCR_EConsumableFailReason.NONE)
	{
		return CanApplyEffect(target, user, failReason);
	}
		
	//------------------------------------------------------------------------------------------------
	void CEN_Medical_ConsumableMorphine()
	{
		m_eConsumableType = SCR_EConsumableType.MORPHINE;
	}
}
