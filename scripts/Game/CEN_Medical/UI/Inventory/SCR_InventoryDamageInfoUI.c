//------------------------------------------------------------------------------------------------
//! UI Script
//! Inventory Slot UI Layout
[EntityEditorProps(category: "GameScripted/UI/Inventory", description: "Inventory Item Info UI class")]
modded class SCR_InventoryDamageInfoUI : ScriptedWidgetComponent
{
	protected ImageWidget							m_wCEN_Medical_PainIconWidget;
	protected TextWidget							m_wCEN_Medical_PainTextWidget;

	protected ResourceName m_sMedicalIconsImageSet 	= "{B9199157B90D6216}UI/Textures/InventoryIcons/Medical/Medical-icons.imageset";
	protected string m_sWarningIcon					= "Warning_UI";
	protected string m_sEpinephrineText 			= "#CEN_Medical-DamageInfo_EpinephrineApplied";
	
	//------------------------------------------------------------------------------------------------
	//! Vanilla morphine becomes epinephrine
	override void SetMorphineStateVisible(bool visible)
	{
		super.SetMorphineStateVisible(visible);
		
		if (!m_wMorphineTextWidget)
			return;
		
		m_wMorphineTextWidget.SetText(m_sEpinephrineText);
	}

	//------------------------------------------------------------------------------------------------
	void CEN_Medical_SetPainStateVisible(bool visible, string painText)
	{
		if (!m_sMedicalIconsImageSet || !m_wCEN_Medical_PainIconWidget || !m_wCEN_Medical_PainTextWidget)
			return;

		m_wCEN_Medical_PainIconWidget.LoadImageFromSet(0, m_sMedicalIconsImageSet, m_sWarningIcon);
		m_wCEN_Medical_PainIconWidget.SetVisible(visible);
		
		m_wCEN_Medical_PainTextWidget.SetText(painText);
		m_wCEN_Medical_PainTextWidget.SetVisible(visible);
	}

	//------------------------------------------------------------------------------------------------
	override void HandlerAttached(Widget w)
	{
		super.HandlerAttached(w);
		m_wCEN_Medical_PainIconWidget = ImageWidget.Cast( w.FindAnyWidget( "CEN_Medical_PainHint_Icon" ) );
		m_wCEN_Medical_PainTextWidget = TextWidget.Cast( w.FindAnyWidget( "CEN_Medical_PainHint_Text" ) );
	}
};
