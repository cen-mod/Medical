//! Epinephrine effect (Same as vanilla morphine effect)
[BaseContainerProps()]
class CEN_Medical_ConsumableEpinephrine : SCR_ConsumableMorphine
{
	//------------------------------------------------------------------------------------------------
	void CEN_Medical_ConsumableEpinephrine()
	{
		m_eConsumableType = SCR_EConsumableType.CEN_MEDICAL_EPINEPHRINE;
	}
}
