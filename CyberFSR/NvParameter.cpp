#include "pch.h"
#include "Config.h"
#include "Util.h"
#include "NvParameter.h"
#include "CyberFsr.h"

// NvParameter::Set helper
inline void Set_Member(NvParameter* setee, const char*& memberName, const auto& setValue, const NvParameterType& type)
{
	setee->Set_Internal(memberName, *((unsigned long long*) & setValue), type);
}

void NvParameter::Set(const char* InName, unsigned long long InValue)
{
	Set_Member(this, InName, InValue, NvULL);
}

void NvParameter::Set(const char* InName, float InValue)
{
	Set_Member(this, InName, InValue, NvFloat);
}

void NvParameter::Set(const char* InName, double InValue)
{
	Set_Member(this, InName, InValue, NvDouble);
}

void NvParameter::Set(const char* InName, unsigned int InValue)
{
	Set_Member(this, InName, InValue, NvUInt);
}

void NvParameter::Set(const char* InName, int InValue)
{
	Set_Member(this, InName, InValue, NvInt);
}

void NvParameter::Set(const char* InName, ID3D11Resource* InValue)
{
	Set_Member(this, InName, InValue, NvD3D11Resource);
}

void NvParameter::Set(const char* InName, ID3D12Resource* InValue)
{
	Set_Member(this, InName, InValue, NvD3D12Resource);
}

void NvParameter::Set(const char* InName, void* InValue)
{
	Set_Member(this, InName, InValue, NvVoidPtr);
}

// NvParameter::Get helper
inline auto Get_Member(const NvParameter* getee, const char*& memberName, const auto& value, const NvParameterType& type)
{
	return getee->Get_Internal(memberName, (unsigned long long*) value, type);
}

NVSDK_NGX_Result NvParameter::Get(const char* InName, unsigned long long* OutValue) const
{
	return Get_Member(this, InName, OutValue, NvULL);
}

NVSDK_NGX_Result NvParameter::Get(const char* InName, float* OutValue) const
{
	return Get_Member(this, InName, OutValue, NvFloat);
}

NVSDK_NGX_Result NvParameter::Get(const char* InName, double* OutValue) const
{
	return Get_Member(this, InName, OutValue, NvDouble);
}

NVSDK_NGX_Result NvParameter::Get(const char* InName, unsigned int* OutValue) const
{
	return Get_Member(this, InName, OutValue, NvUInt);
}

NVSDK_NGX_Result NvParameter::Get(const char* InName, int* OutValue) const
{
	return Get_Member(this, InName, OutValue, NvInt);
}

NVSDK_NGX_Result NvParameter::Get(const char* InName, ID3D11Resource** OutValue) const
{
	return Get_Member(this, InName, OutValue, NvD3D11Resource);
}

NVSDK_NGX_Result NvParameter::Get(const char* InName, ID3D12Resource** OutValue) const
{
	return Get_Member(this, InName, OutValue, NvD3D12Resource);
}

NVSDK_NGX_Result NvParameter::Get(const char* InName, void** OutValue) const
{
	return Get_Member(this, InName, OutValue, NvVoidPtr);
}


void NvParameter::Reset()
{
}

// Set_Internal & Get_Internal helper
template <typename Type> 
inline Type& CastTo(auto& InValue) 
{
	return *((Type*) &InValue);
}

// Set_Internal helper
inline void SetNVarWithName(const auto &InVar, const NvParameterType& ParameterType, void* &setVar, const LPCWSTR& name)
{
	setVar = (void*)InVar;
	if (setVar && ParameterType == NvParameterType::NvD3D12Resource) 
		((ID3D12Resource*)setVar)->SetName(name);
}

void NvParameter::Set_Internal(const char* InName, unsigned long long InValue, NvParameterType ParameterType)
{
	switch (Util::NvParameterToEnum(InName))
	{
	case Util::NvParameter::MV_Scale_X:
		MVScaleX = CastTo<float>(InValue);
		break;
	case Util::NvParameter::MV_Scale_Y:
		MVScaleY = CastTo<float>(InValue);
		break;
	case Util::NvParameter::Jitter_Offset_X:
		JitterOffsetX = CastTo<float>(InValue);
		break;
	case Util::NvParameter::Jitter_Offset_Y:
		JitterOffsetY = CastTo<float>(InValue);
		break;
	case Util::NvParameter::Sharpness:
		Sharpness = CastTo<float>(InValue);
		break;
	case Util::NvParameter::Width:
		Width = CastTo<int>(InValue);
		break;
	case Util::NvParameter::Height:
		Height = CastTo<int>(InValue);
		break;
	case Util::NvParameter::DLSS_Render_Subrect_Dimensions_Width:
		Width = CastTo<int>(InValue);
		break;
	case Util::NvParameter::DLSS_Render_Subrect_Dimensions_Height:
		Height = CastTo<int>(InValue);
		break;
	case Util::NvParameter::PerfQualityValue:
		PerfQualityValue = static_cast<NVSDK_NGX_PerfQuality_Value>(InValue);
		break;
	case Util::NvParameter::RTXValue:
		RTXValue = CastTo<int>(InValue);
		break;
	case Util::NvParameter::FreeMemOnReleaseFeature:
		FreeMemOnReleaseFeature = CastTo<int>(InValue);
		break;
	case Util::NvParameter::CreationNodeMask:
		CreationNodeMask = CastTo<int>(InValue);
		break;
	case Util::NvParameter::VisibilityNodeMask:
		VisibilityNodeMask = CastTo<int>(InValue);
		break;
	case Util::NvParameter::Reset:
		ResetRender = CastTo<int>(InValue);
		break;
	case Util::NvParameter::OutWidth:
		OutWidth = CastTo<int>(InValue);
		break;
	case Util::NvParameter::OutHeight:
		OutHeight = CastTo<int>(InValue);
		break;
	case Util::NvParameter::DLSS_Feature_Create_Flags: { // scoping flags reference lifetime
		const int& inFlags = CastTo<int>(InValue);
		Hdr					= inFlags & NVSDK_NGX_DLSS_Feature_Flags_IsHDR;
		EnableSharpening	= inFlags & NVSDK_NGX_DLSS_Feature_Flags_DoSharpening;
		DepthInverted		= inFlags & NVSDK_NGX_DLSS_Feature_Flags_DepthInverted;
		JitterMotion		= inFlags & NVSDK_NGX_DLSS_Feature_Flags_MVJittered;
		LowRes				= inFlags & NVSDK_NGX_DLSS_Feature_Flags_MVLowRes;
		AutoExposure		= inFlags & NVSDK_NGX_DLSS_Feature_Flags_AutoExposure;
		break;
	}// scoping flags reference lifetime
	case Util::NvParameter::DLSS_Input_Bias_Current_Color_Mask:
		SetNVarWithName(InValue, ParameterType, InputBiasCurrentColorMask, L"Color");
		break;
	case Util::NvParameter::Color:
		SetNVarWithName(InValue, ParameterType, Color, L"Color");
		break;
	case Util::NvParameter::Depth:
		SetNVarWithName(InValue, ParameterType, Depth, L"Depth");
		break;
	case Util::NvParameter::MotionVectors:
		SetNVarWithName(InValue, ParameterType, MotionVectors, L"MotionVectors");
		break;
	case Util::NvParameter::Output:
		SetNVarWithName(InValue, ParameterType, Output, L"Output");
		break;
	case Util::NvParameter::TransparencyMask:
		SetNVarWithName(InValue, ParameterType, TransparencyMask, L"TransparencyMask");
		break;
	case Util::NvParameter::ExposureTexture:
		SetNVarWithName(InValue, ParameterType, ExposureTexture, L"ExposureTexture");
		break;
	}
}

NVSDK_NGX_Result NVSDK_CONV NVSDK_NGX_DLSS_GetOptimalSettingsCallback(NVSDK_NGX_Parameter* InParams);
NVSDK_NGX_Result NVSDK_CONV NVSDK_NGX_DLSS_GetStatsCallback(NVSDK_NGX_Parameter* InParams);

NVSDK_NGX_Result NvParameter::Get_Internal(const char* InName, unsigned long long* OutValue, NvParameterType ParameterType) const
{
	switch (Util::NvParameterToEnum(InName))
	{
	case Util::NvParameter::Sharpness:
		CastTo<float>(OutValue) = Sharpness;
		break;
	case Util::NvParameter::SuperSampling_Available:
		CastTo<int>(OutValue) = true;
		break;
	case Util::NvParameter::SuperSampling_FeatureInitResult:
		CastTo<int>(OutValue) = NVSDK_NGX_Result_Success;
		break;
	case Util::NvParameter::SuperSampling_NeedsUpdatedDriver:
		CastTo<int>(OutValue) = 0;
		break;
	case Util::NvParameter::SuperSampling_MinDriverVersionMinor:
	case Util::NvParameter::SuperSampling_MinDriverVersionMajor:
		CastTo<int>(OutValue) = 0;
		break;
	case Util::NvParameter::DLSS_Render_Subrect_Dimensions_Width:
		CastTo<int>(OutValue) = Width;
		break;
	case Util::NvParameter::DLSS_Render_Subrect_Dimensions_Height:
		CastTo<int>(OutValue) = Height;
		break;
	case Util::NvParameter::OutWidth:
		CastTo<int>(OutValue) = OutWidth;
		break;
	case Util::NvParameter::OutHeight:
		CastTo<int>(OutValue) = OutHeight;
		break;
	case Util::NvParameter::DLSS_Get_Dynamic_Max_Render_Width:
		CastTo<int>(OutValue) = Width;
		break;
	case Util::NvParameter::DLSS_Get_Dynamic_Max_Render_Height:
		CastTo<int>(OutValue) = Height;
		break;
	case Util::NvParameter::DLSS_Get_Dynamic_Min_Render_Width:
		CastTo<int>(OutValue) = OutWidth;
		break;
	case Util::NvParameter::DLSS_Get_Dynamic_Min_Render_Height:
		CastTo<int>(OutValue) = OutHeight;
		break;
	case Util::NvParameter::DLSSOptimalSettingsCallback:
		CastTo<void*>(OutValue) = NVSDK_NGX_DLSS_GetOptimalSettingsCallback;
		break;
	case Util::NvParameter::DLSSGetStatsCallback:
		CastTo<void*>(OutValue) = NVSDK_NGX_DLSS_GetStatsCallback;
		break;
	case Util::NvParameter::SizeInBytes:
		CastTo<unsigned long long>(OutValue) = 0x1337; //Dummy value
		break;
	case Util::NvParameter::OptLevel:
		CastTo<int>(OutValue) = 0; //Dummy value
		break;
	case Util::NvParameter::IsDevSnippetBranch:
		CastTo<int>(OutValue) = 0; //Dummy value
		break;
	default:
		return NVSDK_NGX_Result_Fail;
		break;
	}
	return NVSDK_NGX_Result_Success;
}

// EvaluateRenderScale helper
inline std::optional<FfxFsr2QualityMode> DLSS2FSR2QualityTable(const NVSDK_NGX_PerfQuality_Value& input)
{
	std::optional<FfxFsr2QualityMode> output;

	switch (input)
	{
	case NVSDK_NGX_PerfQuality_Value_UltraPerformance:
		output = FFX_FSR2_QUALITY_MODE_ULTRA_PERFORMANCE;
		break;
	case NVSDK_NGX_PerfQuality_Value_MaxPerf:
		output = FFX_FSR2_QUALITY_MODE_PERFORMANCE;
		break;
	case NVSDK_NGX_PerfQuality_Value_Balanced:
		output = FFX_FSR2_QUALITY_MODE_BALANCED;
		break;
	case NVSDK_NGX_PerfQuality_Value_MaxQuality:
		output = FFX_FSR2_QUALITY_MODE_QUALITY;
		break;
	case NVSDK_NGX_PerfQuality_Value_UltraQuality:
		output = FFX_FSR2_QUALITY_MODE_ULTRA_QUALITY;
		break;
	default:
		// no correlated value, add some logging?
		break;
	}

	return output;
}

// EvaluateRenderScale helper
inline std::optional<float> GetQualityOverrideRatio(const NVSDK_NGX_PerfQuality_Value& input, const std::shared_ptr<const Config>& config)
{
	std::optional<float> output;

	if (! (config->QualityRatioOverrideEnabled.has_value() && config->QualityRatioOverrideEnabled ))
		return output; // override not enabled

	switch (input)
	{
	case NVSDK_NGX_PerfQuality_Value_UltraPerformance:
		output = config->QualityRatio_UltraPerformance;
		break;
	case NVSDK_NGX_PerfQuality_Value_MaxPerf:
		output = config->QualityRatio_Performance;
		break;
	case NVSDK_NGX_PerfQuality_Value_Balanced:
		output = config->QualityRatio_Balanced;
		break;
	case NVSDK_NGX_PerfQuality_Value_MaxQuality:
		output = config->QualityRatio_Quality;
		break;
	case NVSDK_NGX_PerfQuality_Value_UltraQuality:
		output = config->QualityRatio_UltraQuality;
		break;
	default:
		// no correlated value, add some logging?
		break;
	}

	return output;
}

void NvParameter::EvaluateRenderScale()
{
	const std::shared_ptr<Config>& config = CyberFsrContext::instance()->MyConfig;

	const std::optional<float>& QualityRatio = GetQualityOverrideRatio(PerfQualityValue, config);

	if (QualityRatio.has_value()) {
		OutHeight = (unsigned int)((float)Height / QualityRatio.value());
		OutWidth = (unsigned int)((float)Width / QualityRatio.value());
	}
	else {
		const std::optional<FfxFsr2QualityMode>& fsrQualityMode = DLSS2FSR2QualityTable(PerfQualityValue);

		if (fsrQualityMode.has_value()) {
			ffxFsr2GetRenderResolutionFromQualityMode(&OutWidth, &OutHeight, Width, Height, fsrQualityMode.value());
		}
		else {
			// have to have some sort of default unless we want to crash?
			OutHeight = Height / 2;
			OutWidth = Width / 2;
		}
	}
}

NVSDK_NGX_Result NVSDK_CONV NVSDK_NGX_DLSS_GetOptimalSettingsCallback(NVSDK_NGX_Parameter* InParams)
{
	auto* params = (NvParameter*)InParams;
	params->EvaluateRenderScale();
	return NVSDK_NGX_Result_Success;
}

NVSDK_NGX_Result NVSDK_CONV NVSDK_NGX_DLSS_GetStatsCallback(NVSDK_NGX_Parameter* InParams)
{
	//Somehow check for allocated memory
	//Then set values: SizeInBytes, OptLevel, IsDevSnippetBranch
	return NVSDK_NGX_Result_Success;
}