//-----------------------------------------------------------------------------------------------------------
//! Pain - does not receive damage directly, only via scripted events.
class CEN_Medical_PainHitZone : ScriptedHitZone
{
	//-----------------------------------------------------------------------------------------------------------
	override void OnInit(IEntity pOwnerEntity, GenericComponent pManagerComponent)
	{
		super.OnInit(pOwnerEntity, pManagerComponent);
		SCR_CharacterDamageManagerComponent characterDamageManager = SCR_CharacterDamageManagerComponent.Cast(pManagerComponent);
		if (characterDamageManager)
			characterDamageManager.CEN_Medical_SetPainHitZone(this);
	}
}
