/**
  ******************************************************************************
  * @file    codec_configuration.c
  * @author  Frieder Jespers
  * @version V1.0.0
  * @date    03/09/2016
  * @brief   This file contains the initialization for ADC-Multichannel-use
  * with DMA-Controller
  ******************************************************************************
  * @copy
  */

/* Includes ------------------------------------------------------------------*/
#include "codec_configuration.h"
/* Private typedef -----------------------------------------------------------*/
I2C_InitTypeDef I2C_Init_Struct;
I2S_InitTypeDef I2S_Init_Struct;
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

//*******************************************************************
/**
  * @brief  Initialization of Hardware for codec Communication: GPIO, I2S, I2C
  * @param  
  * @retval None
  */
void codec_Init(void){
	GPIO_InitTypeDef GPIO_Init_Struct;
	GPIO_StructInit(&GPIO_Init_Struct);

	//*******************************************************************
	//Port-Clock enable
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA | RCC_AHB1Periph_GPIOB | RCC_AHB1Periph_GPIOC | RCC_AHB1Periph_GPIOD, ENABLE);


	//*******************************************************************
	//GPIO Init

	GPIO_Init_Struct.GPIO_Pin = CODEC_RESET_PIN;
	GPIO_Init_Struct.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_Init_Struct.GPIO_OType = GPIO_OType_PP;
	GPIO_Init_Struct.GPIO_PuPd = GPIO_PuPd_DOWN;
	GPIO_Init_Struct.GPIO_Speed = GPIO_Speed_50MHz;

	GPIO_Init(GPIOD, &GPIO_Init_Struct);

	//*******************************************************************
	//I2C GPIO Init

	GPIO_Init_Struct.GPIO_Pin = I2C_SCL_PIN|I2C_SDA_PIN;
	GPIO_Init_Struct.GPIO_Mode = GPIO_Mode_AF;
	GPIO_Init_Struct.GPIO_OType = GPIO_OType_OD;
	GPIO_Init_Struct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init_Struct.GPIO_Speed = GPIO_Speed_50MHz;

	GPIO_Init(GPIOB, &GPIO_Init_Struct);

	GPIO_PinAFConfig(GPIOB, GPIO_PinSource6,GPIO_AF_I2C1);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource9,GPIO_AF_I2C1);

	//*******************************************************************
	//I2S GPIO Init
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1 | RCC_APB1Periph_SPI3, ENABLE);
	RCC_PLLI2SCmd(ENABLE);
	GPIO_Init_Struct.GPIO_Pin = I2S3_MCLK_PIN|I2S3_SCLK_PIN|I2S3_SD_PIN;
	GPIO_Init_Struct.GPIO_OType = GPIO_OType_PP;

	GPIO_Init(GPIOC, &GPIO_Init_Struct);

	GPIO_Init_Struct.GPIO_Pin = I2S3_WS_PIN;

	GPIO_Init(GPIOA, &GPIO_Init_Struct);

	GPIO_PinAFConfig(GPIOA, GPIO_PinSource4,GPIO_AF_SPI3);
	GPIO_PinAFConfig(GPIOC, GPIO_PinSource7,GPIO_AF_SPI3);
	GPIO_PinAFConfig(GPIOC, GPIO_PinSource10,GPIO_AF_SPI3);
	GPIO_PinAFConfig(GPIOC, GPIO_PinSource12,GPIO_AF_SPI3);

	//turn Codec off
	GPIO_ResetBits(GPIOD, CODEC_RESET_PIN);

	//*******************************************************************
	//Init SPI3

	//*******************************************************************
	//Init I2S Port
	SPI_I2S_DeInit(CODEC_I2S);
	I2S_Init_Struct.I2S_AudioFreq = I2S_AudioFreq_48k;
	I2S_Init_Struct.I2S_MCLKOutput = I2S_MCLKOutput_Enable;
	I2S_Init_Struct.I2S_Mode = I2S_Mode_MasterTx;
	I2S_Init_Struct.I2S_DataFormat = I2S_DataFormat_16b;
	I2S_Init_Struct.I2S_Standard = I2S_Standard_Phillips;
	I2S_Init_Struct.I2S_CPOL = I2S_CPOL_Low;

	I2S_Init(CODEC_I2S,&I2S_Init_Struct);

	//*******************************************************************
	//Init I2C Port
	I2C_DeInit(CODEC_I2C);
	I2C_Init_Struct.I2C_ClockSpeed = 10000;
	I2C_Init_Struct.I2C_Mode = I2C_Mode_I2C;
	I2C_Init_Struct.I2C_OwnAddress1 = CORE_I2C_ADDRESS;
	I2C_Init_Struct.I2C_Ack = I2C_Ack_Enable;
	I2C_Init_Struct.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
	I2C_Init_Struct.I2C_DutyCycle = I2C_DutyCycle_2;

	I2C_Cmd(CODEC_I2C, ENABLE);
	I2C_Init(CODEC_I2C, &I2C_Init_Struct);
}

//*******************************************************************
/**
  * @brief  Sends Configuration Bytes to codec via I2C
  * @param  Codec_Config_Bytes: Array of Configuration Bytes for CS43L22
  * @param	Codec_Config_Byte_Amount: Array Size
  * @retval None
  */
void send_Codec_Config(uint8_t Codec_Config_Bytes[],uint8_t Codec_Config_Byte_Amount){

	//while(I2C_GetFlagStatus(CODEC_I2C,I2C_FLAG_BUSY));//wait until I2C Bus is ready

	I2C_GenerateSTART(CODEC_I2C, ENABLE);// Generates Startcondition for transmit
	while(!I2C_GetFlagStatus(CODEC_I2C,I2C_FLAG_SB));// Wait until Start condition is ready

	I2C_Send7bitAddress(CODEC_I2C,CODEC_I2C_ADDRESS,I2C_Direction_Transmitter); //Sends Address of Audio-Codec
	while(!I2C_CheckEvent(CODEC_I2C, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED)); //Wait until I2C is configured to Master transceiver mode

	for(int i = 0;i<Codec_Config_Byte_Amount;++i){
		I2C_SendData(CODEC_I2C,Codec_Config_Bytes[i]);
		while(!I2C_CheckEvent(CODEC_I2C,I2C_EVENT_MASTER_BYTE_TRANSMITTING));//wait until byte is sent
	}

	while(!I2C_GetFlagStatus(CODEC_I2C,I2C_FLAG_BTF));//Wait until transmit finished

	I2C_GenerateSTOP(CODEC_I2C,ENABLE);//Disable I2C
}

//*******************************************************************
/**
  * @brief  Initialize codec for audio transfer
  * @param  None
  * @retval None
  */
void codec_Configuration(void){
	uint8_t Codec_Config_Buffer[2];
	uint8_t Codec_Received_Data_Buffer;

	GPIO_SetBits(GPIOD,CODEC_RESET_PIN);//Enable Codec
	for(int i = 0;i<1000000;++i); //wait for power on time

	//*******************************************************************
	//Keep codec Power down
	Codec_Config_Buffer[0]= CODEC_MAP_PWR_CTRL1;
	Codec_Config_Buffer[1]= 0x01;//Powered down
	send_Codec_Config(Codec_Config_Buffer,2);

	//printf("1");
	//*******************************************************************
	//Initialisation sequence
	Codec_Config_Buffer[0]= 0x00;
	Codec_Config_Buffer[1]= 0x99;
	send_Codec_Config(Codec_Config_Buffer,2);
	//printf("2");
	Codec_Config_Buffer[0] = 0x47;
	Codec_Config_Buffer[1] = 0x80;
	send_Codec_Config(Codec_Config_Buffer, 2);

	Codec_Received_Data_Buffer = receive_Codec_Data(0x32);

	Codec_Config_Buffer[0] = 0x32;
	Codec_Config_Buffer[1] = Codec_Received_Data_Buffer | 0x80;
	send_Codec_Config(Codec_Config_Buffer, 2);

	Codec_Received_Data_Buffer = receive_Codec_Data(0x32);

	Codec_Config_Buffer[0] = 0x32;
	Codec_Config_Buffer[1] = Codec_Received_Data_Buffer & (~0x80);
	send_Codec_Config(Codec_Config_Buffer, 2);

	Codec_Config_Buffer[0] = 0x00;
	Codec_Config_Buffer[1] = 0x00;
	send_Codec_Config(Codec_Config_Buffer, 2);

	//*******************************************************************
	//Send Configuration Bytes
	//*******************************************************************

	//Power Control
	Codec_Config_Buffer[0] = CODEC_MAP_PWR_CTRL2;
	Codec_Config_Buffer[1] = 0xAA;//Headphone(first nibble) and Speaker(second nibble) power always on
	send_Codec_Config(Codec_Config_Buffer, 2);

	//Playback Control: Headphone Gain,Volume Setting,Inverting signal
	Codec_Config_Buffer[0] = CODEC_MAP_PLAYBACK_CTRL1;
	Codec_Config_Buffer[1] = 0x70;//Headphone Gain: 0,6047, Single Volume control for every Channel, no mute, no inversion
	send_Codec_Config(Codec_Config_Buffer, 2);

	//Clock Control: Auto -Clock-Detection, Single Speed Mode
	Codec_Config_Buffer[0] = CODEC_MAP_CLK_CTRL;
	Codec_Config_Buffer[1] = 0x80;//Auto-Clock-Detection enable,Single Speed Mode
	send_Codec_Config(Codec_Config_Buffer, 2);

	//Interface Control1: Communication Mode: I2S Datasize: 16 Bit
	Codec_Config_Buffer[0] = CODEC_MAP_IF_CTRL1;
	Codec_Config_Buffer[1] = 0x07;//Communication Mode: I2S(1<<2) Datasize: 16 Bit(1<<0)(1<<1)
	send_Codec_Config(Codec_Config_Buffer, 2);

	//Analog Control1: Disable Soft ramp, Zero Cross,Passthrough gang control
	Codec_Config_Buffer[0] = CODEC_MAP_ANALOG_SET;
	Codec_Config_Buffer[1] = 0x00;
	send_Codec_Config(Codec_Config_Buffer, 2);

	//Volume Control A: 0dB gain from input
	Codec_Config_Buffer[0] = CODEC_MAP_PCMA_VOL;
	Codec_Config_Buffer[1] = 0x50;
	send_Codec_Config(Codec_Config_Buffer, 2);

	//Volume Control A: 0dB gain from input
	Codec_Config_Buffer[0] = CODEC_MAP_PCMB_VOL;
	Codec_Config_Buffer[1] = 0x50;
	send_Codec_Config(Codec_Config_Buffer, 2);

	//Tone Control: 0dB gain from input
	Codec_Config_Buffer[0] = CODEC_MAP_TONE_CTRL;
	Codec_Config_Buffer[1] = 0x88;
	send_Codec_Config(Codec_Config_Buffer, 2);

	//Switch on Codec-Power
	Codec_Config_Buffer[0]= CODEC_MAP_PWR_CTRL1;
	Codec_Config_Buffer[1]= 0x9E;//Powered up
	send_Codec_Config(Codec_Config_Buffer,2);
}

//*******************************************************************
/**
  * @brief  Receive Configuration Bytes to codec via I2C
  * @param  Codec_Register_Adress: 8-Bit Codec-Address for read-out
  * @retval Codec_Received_Byte: received Value from Codec
  */
uint8_t receive_Codec_Data(uint8_t Codec_Register_Address){

	uint8_t Codec_Received_Byte;//received data buffer
	//*******************************************************************
	while(I2C_GetFlagStatus(CODEC_I2C,I2C_FLAG_BUSY));//wait until I2C ready

	I2C_GenerateSTART(CODEC_I2C,ENABLE);//Start I2C Communication
	while(!I2C_GetFlagStatus(CODEC_I2C,I2C_FLAG_SB));//wait until Startcondition is ready

	I2C_Send7bitAddress(CODEC_I2C,CODEC_I2C_ADDRESS,I2C_Direction_Transmitter);//Address Codec
	while(!I2C_CheckEvent(CODEC_I2C,I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));//wait until transmission finished

	I2C_SendData(CODEC_I2C,Codec_Register_Address);//Send address for transmission
	while(!I2C_CheckEvent(CODEC_I2C,I2C_EVENT_MASTER_BYTE_TRANSMITTING));//wait until transmission finished

	I2C_GenerateSTOP(CODEC_I2C,ENABLE);//Stop I2C Communication
	while(I2C_GetFlagStatus(CODEC_I2C,I2C_FLAG_BUSY));//wait until I2C ready

	I2C_AcknowledgeConfig(CODEC_I2C,DISABLE);//Disable Acknowledge-Bit

	I2C_GenerateSTART(CODEC_I2C,ENABLE);//Start I2C Communication
	while(!I2C_GetFlagStatus(CODEC_I2C,I2C_FLAG_SB));//wait until Start-Condition is ready

	I2C_Send7bitAddress(CODEC_I2C,CODEC_I2C_ADDRESS,I2C_Direction_Receiver);//Set mcu as receiver
	while(!I2C_CheckEvent(CODEC_I2C,I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED));//wait until transmission finished

	while(!I2C_CheckEvent(CODEC_I2C,I2C_EVENT_MASTER_BYTE_RECEIVED));//wait until mcu received byte

	Codec_Received_Byte = I2C_ReceiveData(CODEC_I2C);//Copy received byte

	I2C_GenerateSTOP(CODEC_I2C,ENABLE); // Stop I2C Communication

	return Codec_Received_Byte;
}

//*******************************************************************
/**
  * @brief  Initialization of DMA-Pipeline for audio transmission
  * @param  Codec_DMA_Memory_Address: Start point of I2S-Buffer
  * @retval None
  */
void codec_DMA_Init(void){
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA1, ENABLE);
	//*******************************************************************
	//Init Interrupt
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = DMA1_Stream5_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	//*******************************************************************

	//*******************************************************************
	//Init DMA1
	DMA_InitTypeDef DMA_InitStructure;
	DMA_Cmd(DMA1_Stream5,DISABLE);
	DMA_DeInit(DMA1_Stream5);
	DMA_InitStructure.DMA_Channel = DMA_Channel_0;
	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)(&(SPI3->DR));
	DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)&i2s_Out;
	DMA_InitStructure.DMA_BufferSize = 	I2S_BUFFERSIZE;
	DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;
	DMA_InitStructure.DMA_DIR = DMA_DIR_MemoryToPeripheral;
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
	DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;
	DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_Full;
	DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
	DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
	DMA_Init(DMA1_Stream5,&DMA_InitStructure);
	DMA_DoubleBufferModeConfig(DMA1_Stream5,(uint32_t)(&i2s_Out),DMA_Memory_0);
	DMA_DoubleBufferModeCmd(DMA1_Stream5, ENABLE);


	DMA_ITConfig(DMA1_Stream5,DMA_IT_TC|DMA_IT_HT,ENABLE);//Enable Half Transfer complete and Transfer complete Interrupt
	DMA_Cmd(DMA1_Stream5,ENABLE);//Enable DMA Stream
	SPI_I2S_ITConfig(SPI3,SPI_I2S_IT_TXE,ENABLE);//Enable Interrupts


	SPI_I2S_DMACmd(CODEC_I2S,SPI_I2S_DMAReq_Tx,ENABLE);// Enable DMA for I2S Transfer
	for(int i = 0; i < 100000;i++);
	I2S_Cmd(CODEC_I2S,ENABLE);// Enable I2S Transfer
}



//*******************************************************************

/**
  * @brief  Interrupt Handler DMA1 Stream 5: Copy Output Buffer to I2S Buffer
  * @param  None
  * @retval None
  */

void DMA1_Stream5_IRQHandler(void){
	static int Transfer_complete_counter = 0;

	//Copy first half of Output Buffer to I2S Buffer after half transfer complete
	if(DMA_GetITStatus(DMA1_Stream5,DMA_IT_HTIF5)){//Half transmission complete
		int j = 0;
		for(int i = 0; i<I2S_BUFFERSIZE/2;i+=2,j++){//Iterate over half I2S Buffersize
			i2s_Out[i] = VCO2.Output_Buffer[j];//-32768;//Copy Output Buffer Channel1
			i2s_Out[i+1] = VCO1.Output_Buffer[j];//-32768;//Copy Output Buffer Channel2
		}
		DMA_ClearITPendingBit(DMA1_Stream5,DMA_IT_HTIF5); // Clear HalfTransfer Complete Flag
	 }

	if( DMA_GetITStatus(DMA1_Stream5,DMA_IT_TCIF5) )//Full Transfer complete
	{
		//Blink LED for Transfer Visualization
		Transfer_complete_counter++;
		if(Transfer_complete_counter >= 11){//Toggle LED approx. every second
			Transfer_complete_counter = 0;
			GPIO_ToggleBits(GPIOD,GPIO_Pin_12);
		}
		//Copy second half of Output Buffer to I2S Buffer after full transfer complete
		int j = I2S_BUFFERSIZE/4;
		for(int i = I2S_BUFFERSIZE/2; i<I2S_BUFFERSIZE;i+=2,j++){
			i2s_Out[i] = VCO2.Output_Buffer[j];//-32768;
			i2s_Out[i+1] = VCO1.Output_Buffer[j];//-32768;
		}
		DMA_ClearITPendingBit(DMA1_Stream5,DMA_IT_TCIF5); // Clear Transfer Complete Flag
		Transfer_Complete_Flag=1;//Set Transfer finished Flag for polling in main function
	}
}



