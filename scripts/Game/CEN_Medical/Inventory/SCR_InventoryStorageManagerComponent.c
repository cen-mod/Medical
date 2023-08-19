modded class SCR_ApplicableMedicalItemPredicate : InventorySearchPredicate
{
	override protected bool IsMatch(BaseInventoryStorageComponent storage, IEntity item, array<GenericComponent> queriedComponents, array<BaseItemAttributeData> queriedAttributes)
	{
		SCR_EConsumableType type = SCR_ConsumableItemComponent.Cast(queriedComponents[0]).GetConsumableType();
		bool isMatch = (type == SCR_EConsumableType.BANDAGE)
			|| (type == SCR_EConsumableType.HEALTH)
			|| (type == SCR_EConsumableType.TOURNIQUET)
			|| (type == SCR_EConsumableType.SALINE)
			|| (type == SCR_EConsumableType.MORPHINE)
			|| (type == SCR_EConsumableType.CEN_MEDICAL_EPINEPHRINE);

		if (!isMatch)
			return false;

		SCR_ConsumableItemComponent medicalItem = SCR_ConsumableItemComponent.Cast(item.FindComponent(SCR_ConsumableItemComponent));
		SCR_ConsumableEffectHealthItems effect = SCR_ConsumableEffectHealthItems.Cast(medicalItem.GetConsumableEffect());
		if (!effect)
			return false;

		return effect.CanApplyEffectToHZ(characterEntity, characterEntity, hitZoneGroup);
	}
};
