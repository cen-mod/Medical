enum CENMedicalECharacterBloodState
{
BLOOD_VOLUME_CLASS_1_HEMORRHAGE,
BLOOD_VOLUME_CLASS_2_HEMORRHAGE,
BLOOD_VOLUME_CLASS_3_HEMORRHAGE,
BLOOD_VOLUME_CLASS_4_HEMORRHAGE,
BLOOD_VOLUME_FATAL
};
//------------------------------------------------------------------------------------------------
modded class SCR_ChimeraCharacter
{
    protected float m_fCEN_Medical_lastUpdateTime = 0;

    //------------------------------------------------------------------------------------------------
    float CEN_Medical_getLastUpdateTime()
    {
     return m_fCEN_Medical_lastUpdateTime;
    }

    //------------------------------------------------------------------------------------------------
    void CEN_Medical_updateLastUpdateTime()
    {
     m_fCEN_Medical_lastUpdateTime = GetGame().GetWorld().GetWorldTime();
    }
}
//------------------------------------------------------------------------------------------------

class VitalUpdater()
{
 
}

