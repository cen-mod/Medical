
//------------------------------------------------------------------------------------------------
class CEN_Medical_Vitals 
{	
	
	//------------------------------------------------------------------------------------------------
	static void VitalUpdater(SCR_ChimeraCharacter unit )
	{
		float m_fCEN_Medical_missionTime = GetGame().GetWorld().GetWorldTime();
		float m_fCEN_Medical_deltaT = Math.Min( m_fCEN_Medical_missionTime - unit.CEN_Medical_getLastUpdateTime(),10);
		SCR_CharacterDamageManagerComponent damageManagerComponent = SCR_CharacterDamageManagerComponent.Cast(unit.FindComponent(SCR_CharacterDamageManagerComponent));
		
	}
	
	//------------------------------------------------------------------------------------------------
}