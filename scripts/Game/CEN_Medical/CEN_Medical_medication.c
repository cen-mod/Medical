enum CEN_MedicalAdjustments
{
	Medication,
	TimeAdded,
	TimeToMaxEffect,
	MaxTimeInSystem,
	HRAdjust,
	PainAdjust,
	FlowAdjust
}
class CEN_Medical_Medication 
{	
	protected SCR_ConsumableType Var_Medications;
	//array<CEN_MedicalAdjustments> VAR_Medications;
	float GetAjustments()
	{
		float m_fHRtargetAjustments = 0;
		float m_fPainsupressAdjustments = 0;
		float m_fPeripheralresistanceAdjustments = 0;
		float m_fAdjustments = VAR_Medications;
		if( m_fAdjustments != VAR_Medications)
		{
			bool m_bdeleted = false;
			float m_ftimeinsystem = GetGame().GetWorld().GetWorldTime() - CEN_MedicalAdjustments.TimeAdded;
			if(m_ftimeinsystem >= CEN_MedicalAdjustments.MaxTimeInSystem)
			{
				m_bdeleted = true;
			}
		}
	}
}