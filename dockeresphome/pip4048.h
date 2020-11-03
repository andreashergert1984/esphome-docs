#include "esphome.h"

#define SENSOR_CNT 23
#define QPIGSLEN 110

class Pip4048 : public PollingComponent, public UARTDevice {
 TextSensor *xqpigs {nullptr};
 Sensor *xgridvoltage {nullptr};
 Sensor *xgridfrequency {nullptr};
 Sensor *xoutvoltage {nullptr};
 Sensor *xoutfrequency {nullptr};
 Sensor *xloadva {nullptr};
 Sensor *xloadwatt {nullptr};
 Sensor *xloadpct {nullptr};
 Sensor *xbusvoltage {nullptr};
 Sensor *xbatteryvoltage {nullptr};
 Sensor *xbatterychargingcurrent {nullptr};
 Sensor *xbatterycapacity {nullptr};
 Sensor *xinvertertemperature {nullptr};
 Sensor *xpvinputcurrent {nullptr};
 Sensor *xpvinputvoltage {nullptr};
 Sensor *xsccvoltage {nullptr};
 Sensor *xbatterydischargecurrent {nullptr};
 Sensor *xloadstatus {nullptr};
 Sensor *xchargingstatus {nullptr};
 Sensor *xsccchargingstatus {nullptr};
 Sensor *xacchargingstatus {nullptr};
 Sensor *xpvinputpower {nullptr};
 
 TextSensor *xqpiri {nullptr};
 TextSensor *xqmod {nullptr};
 TextSensor *xmode {nullptr};

 
 Sensor *xGridRatingVoltage {nullptr};
 Sensor *xGridRatingCurrent {nullptr};
 Sensor *xACOutputRatingVoltage {nullptr};
 Sensor *xACOutputRatingFrequency {nullptr};
 Sensor *xACOutputRatingCurrent {nullptr};
 Sensor *xACOutputRatingApparentPower {nullptr};
 Sensor *xACOutputRatingActivePower {nullptr};
 Sensor *xBatteryRatingVoltage {nullptr};
 Sensor *xBatteryReChargeVoltage {nullptr};
 Sensor *xBatteryUnderVoltage {nullptr};
 Sensor *xBatteryBulkVoltage {nullptr};
 Sensor *xBatteryFloatVoltage {nullptr};
 Sensor *xBatteryType {nullptr};
 Sensor *xCurrentMaxACChargingCurrent {nullptr};
 Sensor *xCurrentMaxChargingCurrent {nullptr};
 Sensor *xInputVoltageRange {nullptr};
 Sensor *xOutputSourcePriority {nullptr};
 Sensor *xChargerSourcePriority {nullptr};
 Sensor *xParallelMaxNum {nullptr};
 Sensor *xMachineType {nullptr};
 Sensor *xTopology {nullptr};
 Sensor *xOutputMode {nullptr};
 Sensor *xBatteryReDischargeVoltage {nullptr};
 Sensor *xPVOKConditionForParallel {nullptr};
 Sensor *xPVPowerBalance {nullptr};
 
	
 
 
 String currentSensor;
 String lastSensor = String("QPIRI");
 unsigned long currentSensorStartTime;
 char input[120];
 unsigned int position = 0;
 String currentInput;
 byte currentResultStage;
	/*
		0: no Query in Progress
		1: pending Result
		2: Pending Length verification
		3: Pending CRC-Validation if needed
		4. Pending Data Extraction
		5. Pending Data Update
	*/

//Temp-Data
int publishcounter;
String qpigs;
float gridvoltage;
float gridfrequency;
float outvoltage;
float outfrequency;
int loadva;
int loadwatt;
int loadpct;
int busvoltage;
float batteryvoltage;
int batterychargingcurrent;
int batterycapacity;
int invertertemperature;
int pvinputcurrent;
float pvinputvoltage;
float sccvoltage;
int batterydischargecurrent;
int loadstatus;
int chargingstatus;
int sccchargingstatus;
int acchargingstatus;
float pvinputpower;
String mode;

String qpiri;
/*
float GridRatingVoltage;
float GridRatingCurrent;
float ACOutputRatingVoltage;
float ACOutputRatingFrequency;
float ACOutputRatingCurrent;
int ACOutputRatingApparentPower;
int ACOutputRatingActivePower;
float BatteryRatingVoltage;
float BatteryReChargeVoltage;
float BatteryUnderVoltage;
float BatteryBulkVoltage;
float BatteryFloatVoltage;
int BatteryType;
/*
int CurrentMaxACChargingCurrent;
int CurrentMaxChargingCurrent;
int InputVoltageRange;
int OutputSourcePriority;
int ChargerSourcePriority;
int ParallelMaxNum;
int MachineType;
int Topology;
int OutputMode;
float BatteryReDischargeVoltage;
int PVOKConditionForParallel;
int PVPowerBalance;
*/
String qmod;


 public:
  Pip4048(UARTComponent *parent, 
	TextSensor *qpigs,
	Sensor *gridvoltage,
	Sensor *gridfrequency,
	Sensor *outvoltage,
	Sensor *outfrequency,
	Sensor *loadva,
	Sensor *loadwatt,
	Sensor *loadpct,
	Sensor *busvoltage,
	Sensor *batteryvoltage,
	Sensor *batterychargingcurrent,
	Sensor *batterycapacity,
	Sensor *invertertemperature,
	Sensor *pvinputcurrent, 
	Sensor *pvinputvoltage,
	Sensor *sccvoltage,
	Sensor *batterydischargecurrent,
	Sensor *loadstatus,
	Sensor *chargingstatus,
	Sensor *sccchargingstatus,
	Sensor *acchargingstatus,
	Sensor *pvinputpower,
	TextSensor *qpiri,
	TextSensor *qmod,
	TextSensor *mode
/*
	Sensor *GridRatingVoltage,
	Sensor *GridRatingCurrent,
	Sensor *ACOutputRatingVoltage,
	Sensor *ACOutputRatingFrequency,
	Sensor *ACOutputRatingCurrent,
	Sensor *ACOutputRatingApparentPower,
	Sensor *ACOutputRatingActivePower,
	Sensor *BatteryRatingVoltage,
	Sensor *BatteryReChargeVoltage,
	Sensor *BatteryUnderVoltage,
	Sensor *BatteryBulkVoltage,
	Sensor *BatteryFloatVoltage,
	Sensor *BatteryType

/*
	Sensor *CurrentMaxACChargingCurrent,
	Sensor *CurrentMaxChargingCurrent,
	Sensor *InputVoltageRange,
	Sensor *OutputSourcePriority,
	Sensor *ChargerSourcePriority,
	Sensor *ParallelMaxNum,
	Sensor *MachineType,
	Sensor *Topology,
	Sensor *OutputMode,
	Sensor *BatteryReDischargeVoltage,
	Sensor *PVOKConditionForParallel,
	Sensor *PVPowerBalance
*/

	
	) : UARTDevice(parent) , 
		xqpigs(qpigs), 
		xgridvoltage(gridvoltage),
		xgridfrequency(gridfrequency),
		xoutvoltage(outvoltage),
		xoutfrequency(outfrequency),
		xloadva(loadva),
		xloadwatt(loadwatt),
		xloadpct(loadpct),
		xbusvoltage(busvoltage),
		xbatteryvoltage(batteryvoltage),
		xbatterychargingcurrent(batterychargingcurrent),
		xbatterycapacity(batterycapacity),
		xinvertertemperature(invertertemperature),
		xpvinputcurrent(pvinputcurrent),
		xpvinputvoltage(pvinputvoltage),
		xsccvoltage(sccvoltage),
		xbatterydischargecurrent(batterydischargecurrent),
		xloadstatus(loadstatus),
		xchargingstatus(chargingstatus),
		xsccchargingstatus(sccchargingstatus),
		xacchargingstatus(acchargingstatus),
		xpvinputpower(pvinputpower),
		xqpiri(qpiri),
		xqmod(qmod),
		xmode(mode)
/*		
		xGridRatingVoltage(GridRatingVoltage),
		xGridRatingCurrent(GridRatingCurrent),
		xACOutputRatingVoltage(ACOutputRatingVoltage),
		xACOutputRatingFrequency(ACOutputRatingFrequency),
		xACOutputRatingCurrent(ACOutputRatingCurrent),
		xACOutputRatingApparentPower(ACOutputRatingApparentPower),
		xACOutputRatingActivePower(ACOutputRatingActivePower),
		xBatteryRatingVoltage(BatteryRatingVoltage),
		xBatteryReChargeVoltage(BatteryReChargeVoltage),
		xBatteryUnderVoltage(BatteryUnderVoltage),
		xBatteryBulkVoltage(BatteryBulkVoltage),
		xBatteryFloatVoltage(BatteryFloatVoltage),
		xBatteryType(BatteryType)
/*		xCurrentMaxACChargingCurrent(CurrentMaxACChargingCurrent),
		xCurrentMaxChargingCurrent(CurrentMaxChargingCurrent),
		xInputVoltageRange(InputVoltageRange),
		xOutputSourcePriority(OutputSourcePriority),
		xChargerSourcePriority(ChargerSourcePriority),
		xParallelMaxNum(ParallelMaxNum),
		xMachineType(MachineType),
		xTopology(Topology),
		xOutputMode(OutputMode),
		xBatteryReDischargeVoltage(BatteryReDischargeVoltage),
		xPVOKConditionForParallel(PVOKConditionForParallel),
		xPVPowerBalance(PVPowerBalance)
*/


		{}


  
  void emptyUARTBuffer()
  {
  	while (available())
	{
		read();
	}	
	this->position = 0;
	currentResultStage	= 0;
	
	ESP_LOGD("pip4048", "UART buffer emptied");
  }
  void getQPIGS()
  {
  		if (currentSensor.length() > 0)
  		{
  			ESP_LOGD("pip4048", "wanted to start QPIGS but %s was still active",currentSensor.c_str());
  		} else
  		{
  			this->emptyUARTBuffer();
  			currentResultStage = 1;
  			currentSensor = String("QPIGS");
  			lastSensor = String("QPIGS");
   	    	ESP_LOGD("pip4048", "sending QPIGS");

  			byte cmd[8] = {  'Q', 'P','I','G', 'S',0xB7,0xA9,0x0D};
  	    	write_array(cmd,8);
  	    	currentSensorStartTime = millis();
  		}
  		return;
	
  }
  void getQPIRI()
  {
  		if (currentSensor.length() > 0)
  		{
  			ESP_LOGD("pip4048", "wanted to start QPIRI but %s was still active",currentSensor.c_str());
  		} else
  		{
  			this->emptyUARTBuffer();
  			currentResultStage = 1;
  			currentSensor = String("QPIRI");
  			lastSensor = String("QPIRI");
   	    	ESP_LOGD("pip4048", "sending QPIRI");

  			byte cmd[8] = {  'Q', 'P','I','R', 'I',0xF8,0x54,0x0D};
  	    	write_array(cmd,8);
  	    	currentSensorStartTime = millis();
  		}
		return;
  }
  void getQMOD()
  {
  		if (currentSensor.length() > 0)
  		{
  			ESP_LOGD("pip4048", "wanted to start QMOD but %s was still active",currentSensor.c_str());
  		} else
  		{
  			this->emptyUARTBuffer();
  			currentResultStage = 1;
  			currentSensor = String("QMOD");
  			lastSensor = String("QMOD");
   	    	ESP_LOGD("pip4048", "sending QMOD");

  			byte cmd[7] = {  'Q', 'M','O','D',0x49,0xC1,0x0D};
  	    	write_array(cmd,7);
  	    	currentSensorStartTime = millis();
  		}
		return;
  }
  
uint16_t calc_crc(char *msg,int n)
{
  // Initial value. xmodem uses 0xFFFF but this example
  // requires an initial value of zero.
  uint16_t x = 0;

  while(n--) {
    x = crc_xmodem_update(x, (uint16_t)*msg++);
  }
  return(x);
}

// See bottom of this page: http://www.nongnu.org/avr-libc/user-manual/group__util__crc.html
// Polynomial: x^16 + x^12 + x^5 + 1 (0x1021)
uint16_t crc_xmodem_update (uint16_t crc, uint8_t data)
{
  int i;

  crc = crc ^ ((uint16_t)data << 8);
  for (i=0; i<8; i++) {
    if (crc & 0x8000)
      crc = (crc << 1) ^ 0x1021; //(polynomial = 0x1021)
    else
      crc <<= 1;
  }
  return crc;
}


  void setup() override {
    this->set_update_interval(10000);
    getQPIGS();
  }

  void loop() override {
  	uint16_t crc16;
  	char in;
  	String data;
  	if (currentSensor.length() > 0 && (millis() - currentSensorStartTime > 4000))
  	{
  		ESP_LOGD("pip4048", "Timeout for %s",currentSensor.c_str());
  		currentSensor = String("");
  		this->emptyUARTBuffer();
  	}	
  	if (currentSensor.length() > 0)
  	{
  		switch(currentResultStage)
  		{
  			case 1: //pending result
		  		if (available())
		  	    {
		  	    	in = read();
		  	    	input[position] = in;
		  	    	position++;
		  	    	if (in == '\r')
		  	    	{
		  	    		input[position] = 0;
						ESP_LOGD("pip4048", "%s EOS received with %d chars",currentSensor.c_str(),position);
						currentResultStage = 2; // set pending Length Check
						return;
		  	    	}
		  	    }
		  	    return;
		  	    break;
		  	case 2:	//pending length check
				if (currentSensor == "QPIGS" && position == 110)
				{
					ESP_LOGD("pip4048", "%s length check passed with %d bytes",currentSensor.c_str(),position);
					currentResultStage = 3;
					return;
				}
				if (currentSensor == "QPIRI" && position == 102)
				{
					ESP_LOGD("pip4048", "%s length check passed with %d bytes",currentSensor.c_str(),position);
					currentResultStage = 3;
					return;
				}
				if (currentSensor == "QMOD" && position == 5)
				{
					ESP_LOGD("pip4048", "%s length check passed with %d bytes",currentSensor.c_str(),position);
					currentResultStage = 3;
					return;
				}
				ESP_LOGD("pip4048", "%s length check failed with %d bytes",currentSensor.c_str(),position);
				data = String(input);

//				ESP_LOGD("pip4048", "%s data was: %s",currentSensor.c_str(),data.c_str());
				currentSensor = String("");
				emptyUARTBuffer();
				if (currentSensor == "QPIGS") {getQPIGS();}
				if (currentSensor == "QPIRI") {getQPIRI();}
				if (currentSensor == "QMOD") {getQMOD();}

				return;
		  		break;
			case 3: 	//pending crc check
	  			crc16 = calc_crc(input,position-3);
	  			if (highByte(crc16) == lowByte(input[position-3]) && lowByte(crc16) == lowByte(input[position-2]))
	   			{
	   				
					ESP_LOGD("pip4048", "%s CRC OK",currentSensor.c_str());
					input[position-1]=0;
					input[position-2]=0;
					input[position-3]=0;
					currentResultStage = 4;
					return;

				} 
				ESP_LOGD("pip4048", "%s CRC NOT OK",currentSensor.c_str());
				currentSensor = String("");
				emptyUARTBuffer();
				if (currentSensor == "QPIGS") {getQPIGS();}
				if (currentSensor == "QPIRI") {getQPIRI();}
				if (currentSensor == "QMOD") {getQMOD();}
				return;
				break;
			case 4:		//pending data Extraction
				if (currentSensor == "QPIRI")
				{
					data = String(input);
      				ESP_LOGD("pip4048", "QPIRI data: %s",data.c_str());
      				qpiri = data.c_str();

				}	
				if (currentSensor == "QMOD")
				{
					data = String(input);
      				ESP_LOGD("pip4048", "QMOD data: %s",data.c_str());
      				qmod = data.c_str();
					mode = data.substring(1,2);
				}
				if (currentSensor == "QPIGS")
				{
      				data = String(input);
      				ESP_LOGD("pip4048", "QPIGS data: %s",data.c_str());
      				qpigs = data.c_str();
					gridvoltage = data.substring(1,5).toFloat();
					gridfrequency = data.substring(7,10).toFloat();
					outvoltage = data.substring(12,16).toFloat();
					outfrequency = data.substring(18,21).toFloat();
					loadva = data.substring(23,27).toInt();
					loadwatt = data.substring(28,32).toInt();
					loadpct = data.substring(34,36).toInt();
					busvoltage = data.substring(37,40).toInt();
					batteryvoltage = data.substring(41,46).toFloat();
					batterychargingcurrent = data.substring(47,50).toInt();
					batterycapacity = data.substring(51,54).toInt();
					invertertemperature = data.substring(55,59).toInt();
					pvinputcurrent = data.substring(60,65).toInt();
					pvinputvoltage = data.substring(65,70).toFloat();
					sccvoltage = data.substring(71,77).toFloat();
					batterydischargecurrent = data.substring(78,83).toInt();
					loadstatus = data.substring(83,91).substring(3,4).toInt();
					chargingstatus = data.substring(83,91).substring(5,6).toInt();
					sccchargingstatus = data.substring(83,91).substring(6,7).toInt();
					acchargingstatus = data.substring(83,91).substring(7,8).toInt();		
					pvinputpower = pvinputcurrent * pvinputvoltage;
				}
				currentResultStage = 5;
				publishcounter = 0;
				return ;
				break;
			case 5:
				if (currentSensor == "QMOD")
				{
					switch (publishcounter)
					{
						case 0: 
		      				xqmod->publish_state(qmod.c_str());
		      				break;
						case 1: 
		      				xmode->publish_state(mode.c_str());
		      				break;		      			
						default:
						
							currentSensor = String("");
							emptyUARTBuffer();					
							currentResultStage = 0;
							getQPIGS();
							return;
							break;
					}
					publishcounter++;
				}
				if (currentSensor == "QPIRI")
				{
					switch (publishcounter)
					{
						case 0: 
		      				xqpiri->publish_state(qpiri.c_str());
		      				break;
						default:
						
							currentSensor = String("");
							emptyUARTBuffer();					
							currentResultStage = 0;
							getQMOD();
							return;
							break;
					}
					publishcounter++;
				}
				if (currentSensor == "QPIGS")
				{
					switch (publishcounter)
					{
						case 0: 
		      				xqpigs->publish_state(qpigs.c_str());
		      				break;
						case 1: 
							xgridvoltage->publish_state(gridvoltage);
		      				break;
						case 2: 
							xgridfrequency->publish_state(gridfrequency);
		      				break;
						case 3: 
							xoutvoltage->publish_state(outvoltage);
		      				break;
						case 4: 
							xoutfrequency->publish_state(outfrequency);
		      				break;
						case 5: 
							xloadva->publish_state(loadva);
		      				break;
						case 6: 
							xloadwatt->publish_state(loadwatt);
		      				break;
						case 7: 
							xloadpct->publish_state(loadpct);
		      				break;
						case 8: 
							xbusvoltage->publish_state(busvoltage);
		      				break;
						case 9: 
							xbatteryvoltage->publish_state(batteryvoltage);
		      				break;
						case 10: 
							xbatterychargingcurrent->publish_state(batterychargingcurrent);
		      				break;
						case 11: 
							xbatterycapacity->publish_state(batterycapacity);
		      				break;
						case 12: 
							xinvertertemperature->publish_state(invertertemperature);
		      				break;
						case 13: 
							xpvinputcurrent->publish_state(pvinputcurrent);
		      				break;
						case 14: 
							xpvinputvoltage->publish_state(pvinputvoltage);
		      				break;
						case 15: 
							xsccvoltage->publish_state(sccvoltage);
		      				break;
						case 16: 
							xbatterydischargecurrent->publish_state(batterydischargecurrent);
		      				break;
						case 17: 
							xloadstatus->publish_state(loadstatus);
		      				break;
						case 18: 
							xchargingstatus->publish_state(chargingstatus);
		      				break;
						case 19: 
							xsccchargingstatus->publish_state(sccchargingstatus);
		      				break;
						case 20: 
							xacchargingstatus->publish_state(acchargingstatus);	
							break;
						case 21: 
							xpvinputpower->publish_state(pvinputpower);	
							break;
						default:
						
							currentSensor = String("");
							emptyUARTBuffer();					
							currentResultStage = 0;
							getQPIRI();
							return;
							break;
					}
					publishcounter++;
				}
				
			return;
			break;
  		}
  		
  	}
  	
  }

  void update() override {

	this->set_update_interval(60000);
//	getSerial();
//	if (lastSensor == "QPIRI")
//	{
		getQPIGS();
//	}
//	if (lastSensor == "QPIGS")
//	{
//		getQPIRI();
//	}


//	getQPIRI();
//	QMOD I 0xC1 0x0d
//	QPIWS 0xB4 0xDA 0x0D

//    val=getParm(vorlaufSoll,sizeof(vorlaufSoll));
//    if (xsensor1 != nullptr)   xsensor1->publish_state(val);

  }
};
