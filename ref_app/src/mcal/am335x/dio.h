#ifndef _DIO_2013_06_29_H_
  #define _DIO_2013_06_29_H_

  #include <cstdint>
  #include <dio_cfg.h>

  constexpr unsigned STD_HIGH = 0x01U;
  constexpr unsigned STD_LOW  = 0x00U;

  typedef std::uint32_t Dio_ChannelType;
  typedef std::uint32_t Dio_PortType;

  typedef struct struct_Dio_ChannelGroupType
  {
    std::uint8_t    offset;
    Dio_PortType    port;
    std::uint16_t   mask;
  }
  Dio_ChannelGroupType;

  typedef std::uint32_t Dio_LevelType;
  typedef std::uint32_t Dio_PortLevelType;

  // *****************************************************************************
  // macros 
  // *****************************************************************************
  #define Port0                               (Dio_PortType)0x00u
  #define Port1                               (Dio_PortType)0x20u
  #define Port2                               (Dio_PortType)0x40u
  #define Port3                               (Dio_PortType)0x60u

  #define Do_Port0_0                          (Dio_ChannelType)0x00u
  #define Do_Port0_1                          (Dio_ChannelType)0x01u
  #define Do_Port0_2                          (Dio_ChannelType)0x02u
  #define Do_Port0_3                          (Dio_ChannelType)0x03u
  #define Do_Port0_4                          (Dio_ChannelType)0x04u
  #define Do_Port0_5                          (Dio_ChannelType)0x05u
  #define Do_Port0_6                          (Dio_ChannelType)0x06u
  #define Do_Port0_7                          (Dio_ChannelType)0x07u
  #define Do_Port0_8                          (Dio_ChannelType)0x08u
  #define Do_Port0_9                          (Dio_ChannelType)0x09u
  #define Do_Port0_10                         (Dio_ChannelType)0x0Au
  #define Do_Port0_11                         (Dio_ChannelType)0x0Bu
  #define Do_Port0_12                         (Dio_ChannelType)0x0Cu
  #define Do_Port0_13                         (Dio_ChannelType)0x0Du
  #define Do_Port0_14                         (Dio_ChannelType)0x0Eu
  #define Do_Port0_15                         (Dio_ChannelType)0x0Fu
  #define Do_Port0_16                         (Dio_ChannelType)0x10u
  #define Do_Port0_17                         (Dio_ChannelType)0x11u
  #define Do_Port0_18                         (Dio_ChannelType)0x12u
  #define Do_Port0_19                         (Dio_ChannelType)0x13u
  #define Do_Port0_20                         (Dio_ChannelType)0x14u
  #define Do_Port0_21                         (Dio_ChannelType)0x15u
  #define Do_Port0_22                         (Dio_ChannelType)0x16u
  #define Do_Port0_23                         (Dio_ChannelType)0x17u
  #define Do_Port0_24                         (Dio_ChannelType)0x18u
  #define Do_Port0_25                         (Dio_ChannelType)0x19u
  #define Do_Port0_26                         (Dio_ChannelType)0x1Au
  #define Do_Port0_27                         (Dio_ChannelType)0x1Bu
  #define Do_Port0_28                         (Dio_ChannelType)0x1Cu
  #define Do_Port0_29                         (Dio_ChannelType)0x1Du
  #define Do_Port0_30                         (Dio_ChannelType)0x1Eu
  #define Do_Port0_31                         (Dio_ChannelType)0x1Fu

  #define Do_Port1_0                          (Dio_ChannelType)0x20u
  #define Do_Port1_1                          (Dio_ChannelType)0x21u
  #define Do_Port1_2                          (Dio_ChannelType)0x22u
  #define Do_Port1_3                          (Dio_ChannelType)0x23u
  #define Do_Port1_4                          (Dio_ChannelType)0x24u
  #define Do_Port1_5                          (Dio_ChannelType)0x25u
  #define Do_Port1_6                          (Dio_ChannelType)0x26u
  #define Do_Port1_7                          (Dio_ChannelType)0x27u
  #define Do_Port1_8                          (Dio_ChannelType)0x28u
  #define Do_Port1_9                          (Dio_ChannelType)0x29u
  #define Do_Port1_10                         (Dio_ChannelType)0x2Au
  #define Do_Port1_11                         (Dio_ChannelType)0x2Bu
  #define Do_Port1_12                         (Dio_ChannelType)0x2Cu
  #define Do_Port1_13                         (Dio_ChannelType)0x2Du
  #define Do_Port1_14                         (Dio_ChannelType)0x2Eu
  #define Do_Port1_15                         (Dio_ChannelType)0x2Fu
  #define Do_Port1_16                         (Dio_ChannelType)0x30u
  #define Do_Port1_17                         (Dio_ChannelType)0x31u
  #define Do_Port1_18                         (Dio_ChannelType)0x32u
  #define Do_Port1_19                         (Dio_ChannelType)0x33u
  #define Do_Port1_20                         (Dio_ChannelType)0x34u
  #define Do_Port1_21                         (Dio_ChannelType)0x35u
  #define Do_Port1_22                         (Dio_ChannelType)0x36u
  #define Do_Port1_23                         (Dio_ChannelType)0x37u
  #define Do_Port1_24                         (Dio_ChannelType)0x38u
  #define Do_Port1_25                         (Dio_ChannelType)0x39u
  #define Do_Port1_26                         (Dio_ChannelType)0x3Au
  #define Do_Port1_27                         (Dio_ChannelType)0x3Bu
  #define Do_Port1_28                         (Dio_ChannelType)0x3Cu
  #define Do_Port1_29                         (Dio_ChannelType)0x3Du
  #define Do_Port1_30                         (Dio_ChannelType)0x3Eu
  #define Do_Port1_31                         (Dio_ChannelType)0x3Fu

  #define Do_Port2_0                          (Dio_ChannelType)0x40u
  #define Do_Port2_1                          (Dio_ChannelType)0x41u
  #define Do_Port2_2                          (Dio_ChannelType)0x42u
  #define Do_Port2_3                          (Dio_ChannelType)0x43u
  #define Do_Port2_4                          (Dio_ChannelType)0x44u
  #define Do_Port2_5                          (Dio_ChannelType)0x45u
  #define Do_Port2_6                          (Dio_ChannelType)0x46u
  #define Do_Port2_7                          (Dio_ChannelType)0x47u
  #define Do_Port2_8                          (Dio_ChannelType)0x48u
  #define Do_Port2_9                          (Dio_ChannelType)0x49u
  #define Do_Port2_10                         (Dio_ChannelType)0x4Au
  #define Do_Port2_11                         (Dio_ChannelType)0x4Bu
  #define Do_Port2_12                         (Dio_ChannelType)0x4Cu
  #define Do_Port2_13                         (Dio_ChannelType)0x4Du
  #define Do_Port2_14                         (Dio_ChannelType)0x4Eu
  #define Do_Port2_15                         (Dio_ChannelType)0x4Fu
  #define Do_Port2_16                         (Dio_ChannelType)0x50u
  #define Do_Port2_17                         (Dio_ChannelType)0x51u
  #define Do_Port2_18                         (Dio_ChannelType)0x52u
  #define Do_Port2_19                         (Dio_ChannelType)0x53u
  #define Do_Port2_20                         (Dio_ChannelType)0x54u
  #define Do_Port2_21                         (Dio_ChannelType)0x55u
  #define Do_Port2_22                         (Dio_ChannelType)0x56u
  #define Do_Port2_23                         (Dio_ChannelType)0x57u
  #define Do_Port2_24                         (Dio_ChannelType)0x58u
  #define Do_Port2_25                         (Dio_ChannelType)0x59u
  #define Do_Port2_26                         (Dio_ChannelType)0x5Au
  #define Do_Port2_27                         (Dio_ChannelType)0x5Bu
  #define Do_Port2_28                         (Dio_ChannelType)0x5Cu
  #define Do_Port2_29                         (Dio_ChannelType)0x5Du
  #define Do_Port2_30                         (Dio_ChannelType)0x5Eu
  #define Do_Port2_31                         (Dio_ChannelType)0x5Fu

  #define Do_Port3_0                          (Dio_ChannelType)0x60u
  #define Do_Port3_1                          (Dio_ChannelType)0x61u
  #define Do_Port3_2                          (Dio_ChannelType)0x62u
  #define Do_Port3_3                          (Dio_ChannelType)0x63u
  #define Do_Port3_4                          (Dio_ChannelType)0x64u
  #define Do_Port3_5                          (Dio_ChannelType)0x65u
  #define Do_Port3_6                          (Dio_ChannelType)0x66u
  #define Do_Port3_7                          (Dio_ChannelType)0x67u
  #define Do_Port3_8                          (Dio_ChannelType)0x68u
  #define Do_Port3_9                          (Dio_ChannelType)0x69u
  #define Do_Port3_10                         (Dio_ChannelType)0x6Au
  #define Do_Port3_11                         (Dio_ChannelType)0x6Bu
  #define Do_Port3_12                         (Dio_ChannelType)0x6Cu
  #define Do_Port3_13                         (Dio_ChannelType)0x6Du
  #define Do_Port3_14                         (Dio_ChannelType)0x6Eu
  #define Do_Port3_15                         (Dio_ChannelType)0x6Fu
  #define Do_Port3_16                         (Dio_ChannelType)0x70u
  #define Do_Port3_17                         (Dio_ChannelType)0x71u
  #define Do_Port3_18                         (Dio_ChannelType)0x72u
  #define Do_Port3_19                         (Dio_ChannelType)0x73u
  #define Do_Port3_20                         (Dio_ChannelType)0x74u
  #define Do_Port3_21                         (Dio_ChannelType)0x75u
  #define Do_Port3_22                         (Dio_ChannelType)0x76u
  #define Do_Port3_23                         (Dio_ChannelType)0x77u
  #define Do_Port3_24                         (Dio_ChannelType)0x78u
  #define Do_Port3_25                         (Dio_ChannelType)0x79u
  #define Do_Port3_26                         (Dio_ChannelType)0x7Au
  #define Do_Port3_27                         (Dio_ChannelType)0x7Bu
  #define Do_Port3_28                         (Dio_ChannelType)0x7Cu
  #define Do_Port3_29                         (Dio_ChannelType)0x7Du
  #define Do_Port3_30                         (Dio_ChannelType)0x7Eu
  #define Do_Port3_31                         (Dio_ChannelType)0x7Fu

  #define Di_Port0_0                          (Dio_ChannelType)0x00u
  #define Di_Port0_1                          (Dio_ChannelType)0x01u
  #define Di_Port0_2                          (Dio_ChannelType)0x02u
  #define Di_Port0_3                          (Dio_ChannelType)0x03u
  #define Di_Port0_4                          (Dio_ChannelType)0x04u
  #define Di_Port0_5                          (Dio_ChannelType)0x05u
  #define Di_Port0_6                          (Dio_ChannelType)0x06u
  #define Di_Port0_7                          (Dio_ChannelType)0x07u
  #define Di_Port0_8                          (Dio_ChannelType)0x08u
  #define Di_Port0_9                          (Dio_ChannelType)0x09u
  #define Di_Port0_10                         (Dio_ChannelType)0x0Au
  #define Di_Port0_11                         (Dio_ChannelType)0x0Bu
  #define Di_Port0_12                         (Dio_ChannelType)0x0Cu
  #define Di_Port0_13                         (Dio_ChannelType)0x0Du
  #define Di_Port0_14                         (Dio_ChannelType)0x0Eu
  #define Di_Port0_15                         (Dio_ChannelType)0x0Fu
  #define Di_Port0_16                         (Dio_ChannelType)0x10u
  #define Di_Port0_17                         (Dio_ChannelType)0x11u
  #define Di_Port0_18                         (Dio_ChannelType)0x12u
  #define Di_Port0_19                         (Dio_ChannelType)0x13u
  #define Di_Port0_20                         (Dio_ChannelType)0x14u
  #define Di_Port0_21                         (Dio_ChannelType)0x15u
  #define Di_Port0_22                         (Dio_ChannelType)0x16u
  #define Di_Port0_23                         (Dio_ChannelType)0x17u
  #define Di_Port0_24                         (Dio_ChannelType)0x18u
  #define Di_Port0_25                         (Dio_ChannelType)0x19u
  #define Di_Port0_26                         (Dio_ChannelType)0x1Au
  #define Di_Port0_27                         (Dio_ChannelType)0x1Bu
  #define Di_Port0_28                         (Dio_ChannelType)0x1Cu
  #define Di_Port0_29                         (Dio_ChannelType)0x1Du
  #define Di_Port0_30                         (Dio_ChannelType)0x1Eu
  #define Di_Port0_31                         (Dio_ChannelType)0x1Fu

  #define Di_Port1_0                          (Dio_ChannelType)0x20u
  #define Di_Port1_1                          (Dio_ChannelType)0x21u
  #define Di_Port1_2                          (Dio_ChannelType)0x22u
  #define Di_Port1_3                          (Dio_ChannelType)0x23u
  #define Di_Port1_4                          (Dio_ChannelType)0x24u
  #define Di_Port1_5                          (Dio_ChannelType)0x25u
  #define Di_Port1_6                          (Dio_ChannelType)0x26u
  #define Di_Port1_7                          (Dio_ChannelType)0x27u
  #define Di_Port1_8                          (Dio_ChannelType)0x28u
  #define Di_Port1_9                          (Dio_ChannelType)0x29u
  #define Di_Port1_10                         (Dio_ChannelType)0x2Au
  #define Di_Port1_11                         (Dio_ChannelType)0x2Bu
  #define Di_Port1_12                         (Dio_ChannelType)0x2Cu
  #define Di_Port1_13                         (Dio_ChannelType)0x2Du
  #define Di_Port1_14                         (Dio_ChannelType)0x2Eu
  #define Di_Port1_15                         (Dio_ChannelType)0x2Fu
  #define Di_Port1_16                         (Dio_ChannelType)0x30u
  #define Di_Port1_17                         (Dio_ChannelType)0x31u
  #define Di_Port1_18                         (Dio_ChannelType)0x32u
  #define Di_Port1_19                         (Dio_ChannelType)0x33u
  #define Di_Port1_20                         (Dio_ChannelType)0x34u
  #define Di_Port1_21                         (Dio_ChannelType)0x35u
  #define Di_Port1_22                         (Dio_ChannelType)0x36u
  #define Di_Port1_23                         (Dio_ChannelType)0x37u
  #define Di_Port1_24                         (Dio_ChannelType)0x38u
  #define Di_Port1_25                         (Dio_ChannelType)0x39u
  #define Di_Port1_26                         (Dio_ChannelType)0x3Au
  #define Di_Port1_27                         (Dio_ChannelType)0x3Bu
  #define Di_Port1_28                         (Dio_ChannelType)0x3Cu
  #define Di_Port1_29                         (Dio_ChannelType)0x3Du
  #define Di_Port1_30                         (Dio_ChannelType)0x3Eu
  #define Di_Port1_31                         (Dio_ChannelType)0x3Fu

  #define Di_Port2_0                          (Dio_ChannelType)0x40u
  #define Di_Port2_1                          (Dio_ChannelType)0x41u
  #define Di_Port2_2                          (Dio_ChannelType)0x42u
  #define Di_Port2_3                          (Dio_ChannelType)0x43u
  #define Di_Port2_4                          (Dio_ChannelType)0x44u
  #define Di_Port2_5                          (Dio_ChannelType)0x45u
  #define Di_Port2_6                          (Dio_ChannelType)0x46u
  #define Di_Port2_7                          (Dio_ChannelType)0x47u
  #define Di_Port2_8                          (Dio_ChannelType)0x48u
  #define Di_Port2_9                          (Dio_ChannelType)0x49u
  #define Di_Port2_10                         (Dio_ChannelType)0x4Au
  #define Di_Port2_11                         (Dio_ChannelType)0x4Bu
  #define Di_Port2_12                         (Dio_ChannelType)0x4Cu
  #define Di_Port2_13                         (Dio_ChannelType)0x4Du
  #define Di_Port2_14                         (Dio_ChannelType)0x4Eu
  #define Di_Port2_15                         (Dio_ChannelType)0x4Fu
  #define Di_Port2_16                         (Dio_ChannelType)0x50u
  #define Di_Port2_17                         (Dio_ChannelType)0x51u
  #define Di_Port2_18                         (Dio_ChannelType)0x52u
  #define Di_Port2_19                         (Dio_ChannelType)0x53u
  #define Di_Port2_20                         (Dio_ChannelType)0x54u
  #define Di_Port2_21                         (Dio_ChannelType)0x55u
  #define Di_Port2_22                         (Dio_ChannelType)0x56u
  #define Di_Port2_23                         (Dio_ChannelType)0x57u
  #define Di_Port2_24                         (Dio_ChannelType)0x58u
  #define Di_Port2_25                         (Dio_ChannelType)0x59u
  #define Di_Port2_26                         (Dio_ChannelType)0x5Au
  #define Di_Port2_27                         (Dio_ChannelType)0x5Bu
  #define Di_Port2_28                         (Dio_ChannelType)0x5Cu
  #define Di_Port2_29                         (Dio_ChannelType)0x5Du
  #define Di_Port2_30                         (Dio_ChannelType)0x5Eu
  #define Di_Port2_31                         (Dio_ChannelType)0x5Fu

  #define Di_Port3_0                          (Dio_ChannelType)0x60u
  #define Di_Port3_1                          (Dio_ChannelType)0x61u
  #define Di_Port3_2                          (Dio_ChannelType)0x62u
  #define Di_Port3_3                          (Dio_ChannelType)0x63u
  #define Di_Port3_4                          (Dio_ChannelType)0x64u
  #define Di_Port3_5                          (Dio_ChannelType)0x65u
  #define Di_Port3_6                          (Dio_ChannelType)0x66u
  #define Di_Port3_7                          (Dio_ChannelType)0x67u
  #define Di_Port3_8                          (Dio_ChannelType)0x68u
  #define Di_Port3_9                          (Dio_ChannelType)0x69u
  #define Di_Port3_10                         (Dio_ChannelType)0x6Au
  #define Di_Port3_11                         (Dio_ChannelType)0x6Bu
  #define Di_Port3_12                         (Dio_ChannelType)0x6Cu
  #define Di_Port3_13                         (Dio_ChannelType)0x6Du
  #define Di_Port3_14                         (Dio_ChannelType)0x6Eu
  #define Di_Port3_15                         (Dio_ChannelType)0x6Fu
  #define Di_Port3_16                         (Dio_ChannelType)0x70u
  #define Di_Port3_17                         (Dio_ChannelType)0x71u
  #define Di_Port3_18                         (Dio_ChannelType)0x72u
  #define Di_Port3_19                         (Dio_ChannelType)0x73u
  #define Di_Port3_20                         (Dio_ChannelType)0x74u
  #define Di_Port3_21                         (Dio_ChannelType)0x75u
  #define Di_Port3_22                         (Dio_ChannelType)0x76u
  #define Di_Port3_23                         (Dio_ChannelType)0x77u
  #define Di_Port3_24                         (Dio_ChannelType)0x78u
  #define Di_Port3_25                         (Dio_ChannelType)0x79u
  #define Di_Port3_26                         (Dio_ChannelType)0x7Au
  #define Di_Port3_27                         (Dio_ChannelType)0x7Bu
  #define Di_Port3_28                         (Dio_ChannelType)0x7Cu
  #define Di_Port3_29                         (Dio_ChannelType)0x7Du
  #define Di_Port3_30                         (Dio_ChannelType)0x7Eu
  #define Di_Port3_31                         (Dio_ChannelType)0x7Fu

  void Dio_WriteChannel(Dio_ChannelType ChannelId, Dio_LevelType Level);

#endif // _DIO_2013_06_29_H_
