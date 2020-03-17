/*
 * GSM_COMMANDS.c
 *
 *  Created on: Jul 30, 2019
 *      Author: rajasekaranp
 */
#include "GSM_COMMAND.h"
#include "stdio.h"
#include "gpio.h"
#include "FreeRTOS.h"
#include "task.h"
#include "string.h"

unsigned int ok_count = 0; //, error = 0;

bool gsm_init() {
	for (int i = 0; i < sizeof(dummy); i++)
		dummy[i] = 0;
	ok_count = 0;
	while (HAL_UART_DeInit(&huart1) != HAL_OK)
		;
	while (HAL_UART_Init(&huart1) != HAL_OK)
		;
	//HAL_UART_DeInit(&huart1);
	//vTaskDelay(1000);
	//HAL_UART_Init(&huart1);

	AT: HAL_UART_Receive(&huart1, (uint8_t*) &dummy, sizeof(dummy), 100);
	HAL_UART_Transmit(&huart1, (uint8_t*) &"AT\r", 3, 100);
	HAL_UART_Receive(&huart1, (uint8_t*) &AT, sizeof(AT), 100);
//	HAL_UART_Transmit(&huart5, (uint8_t*) &AT, sizeof(AT), 100);
	if (strstr(AT, "OK")) {
		ok_count++;
		if (ok_count > 2)
			return true;
		else {
			for (int i = 0; i < sizeof(dummy); i++)
				dummy[i] = 0;
			for (int i = 0; i < sizeof(AT); i++)
				AT[i] = 0;
			goto AT;
		}
	} else
		return false;

}
void GSM_restart() {
	//HAL_UART_Transmit(&huart5, (uint8_t*) "GSM_OFF\r\n", 9, 100);
	HAL_UART_Transmit(&huart1, (uint8_t*) "AT+CPOF\r", 8, 1000);
	vTaskDelay(12000);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET);
	vTaskDelay(1500);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);
	vTaskDelay(18000);
	//HAL_UART_Transmit(&huart5, (uint8_t*) "GSM_ON\r\n", 8, 100);
}
bool gsm_setting() {
	ok_count = 0;

	while (HAL_UART_DeInit(&huart1) != HAL_OK)
		;
	while (HAL_UART_Init(&huart1) != HAL_OK)
		;

//	HAL_UART_Transmit(&huart1, (uint8_t*) &"ate0;&w\r", 8, 100); //with save of echo off
	HAL_UART_Transmit(&huart1, (uint8_t*) &"ate0\r", 5, 100); //without save of echo off
//	__HAL_UART_SEND_REQ(&huart1, UART_RXDATA_FLUSH_REQUEST);
	HAL_UART_Receive(&huart1, (uint8_t*) &dummy, sizeof(dummy), 1000);
	if (strstr(dummy, "OK"))
		ok_count++;
	memset(dummy, 0, sizeof(dummy));

	while (HAL_UART_DeInit(&huart1) != HAL_OK)
		;
	while (HAL_UART_Init(&huart1) != HAL_OK)
		;

//	HAL_UART_Transmit(&huart1, (uint8_t*) &"AT+CIURC=0;&w\r", 14, 100);
//	__HAL_UART_SEND_REQ(&huart1, UART_RXDATA_FLUSH_REQUEST);
//	HAL_UART_Receive(&huart1, (uint8_t*) &dummy, sizeof(dummy), 1000);
	HAL_UART_Transmit(&huart1, (uint8_t*) &"AT+CNSMOD=0\r", 12, 100);
	//	__HAL_UART_SEND_REQ(&huart1, UART_RXDATA_FLUSH_REQUEST);
	HAL_UART_Receive(&huart1, (uint8_t*) &dummy, sizeof(dummy), 1000);
	if (strstr(dummy, "OK"))
		ok_count++;
	memset(dummy, 0, sizeof(dummy));

	while (HAL_UART_DeInit(&huart1) != HAL_OK)
		;
	while (HAL_UART_Init(&huart1) != HAL_OK)
		;

	HAL_UART_Transmit(&huart1, (uint8_t*) &"AT+CGREG=0\r", 11, 100);
	//	__HAL_UART_SEND_REQ(&huart1, UART_RXDATA_FLUSH_REQUEST);
	HAL_UART_Receive(&huart1, (uint8_t*) &dummy, sizeof(dummy), 1000);
	if (strstr(dummy, "OK"))
		ok_count++;
	memset(dummy, 0, sizeof(dummy));

	while (HAL_UART_DeInit(&huart1) != HAL_OK)
		;
	while (HAL_UART_Init(&huart1) != HAL_OK)
		;

	HAL_UART_Transmit(&huart1, (uint8_t*) &"AT+CEREG=0\r", 11, 100);
	//	__HAL_UART_SEND_REQ(&huart1, UART_RXDATA_FLUSH_REQUEST);
	HAL_UART_Receive(&huart1, (uint8_t*) &dummy, sizeof(dummy), 1000);
	if (strstr(dummy, "OK"))
		ok_count++;
	memset(dummy, 0, sizeof(dummy));

	while (HAL_UART_DeInit(&huart1) != HAL_OK)
		;
	while (HAL_UART_Init(&huart1) != HAL_OK)
		;

	HAL_UART_Transmit(&huart1, (uint8_t*) &"AT+AUTOCSQ=0\r", 13, 100);
	//	__HAL_UART_SEND_REQ(&huart1, UART_RXDATA_FLUSH_REQUEST);
	HAL_UART_Receive(&huart1, (uint8_t*) &dummy, sizeof(dummy), 1000);
	if (strstr(dummy, "OK"))
		ok_count++;
	memset(dummy, 0, sizeof(dummy));

	while (HAL_UART_DeInit(&huart1) != HAL_OK)
		;
	while (HAL_UART_Init(&huart1) != HAL_OK)
//		HAL_UART_Transmit(&huart1, (uint8_t*) &"at+cnmi=1,0,0,0,0&w0\r", 21,
//				100);//withsave
		HAL_UART_Transmit(&huart1, (uint8_t*) &"at+cnmi=1,0,0,0,0\r", 21, 100); //without save
//	__HAL_UART_SEND_REQ(&huart1, UART_RXDATA_FLUSH_REQUEST);
	HAL_UART_Receive(&huart1, (uint8_t*) &dummy, sizeof(dummy), 1000);
	if (strstr(dummy, "OK"))
		ok_count++;
	memset(dummy, 0, sizeof(dummy));

//	while (HAL_UART_DeInit(&huart1) != HAL_OK)
//		;
//	while (HAL_UART_Init(&huart1) != HAL_OK)
//		;

//	HAL_UART_Transmit(&huart1, (uint8_t*) &"AT+GSMBUSY=1;&w\r", 16, 100);
//	__HAL_UART_SEND_REQ(&huart1, UART_RXDATA_FLUSH_REQUEST);
//	HAL_UART_Receive(&huart1, (uint8_t*) &dummy, sizeof(dummy), 1000);
//	if (strstr(dummy, "OK"))
//		ok_count++;
//	memset(dummy, 0, sizeof(dummy));

	if (ok_count == 6)
		return true;
	else
		return false;

}
uint8_t *GSM_command(uint8_t *command) {
	uint8_t buffer1[150] = { 0 };
	//uint8_t dummy_read[100] = { 0 };
	//HAL_UART_Receive(&huart1, (uint8_t*) &dummy_read, sizeof(dummy_read), 1000);
	while (HAL_UART_DeInit(&huart1))
		;
	while (HAL_UART_Init(&huart1))
		;
	HAL_UART_Transmit(&huart1, (uint8_t*) command, strlen((char*) command),
			100);
	HAL_UART_Transmit(&huart1, (uint8_t*) "\r\n", 2, 100);
	HAL_UART_Receive(&huart1, (uint8_t*) &buffer1, sizeof(buffer), 2000);
	//	HAL_UART_Transmit(&huart5, (uint8_t*) &"buffer:", 7, 100);
	//	HAL_UART_Transmit(&huart5, (uint8_t*) &buffer, sizeof(buffer), 100);
	uint8_t *rx;
	rx = buffer1;
//	strcpy((char*) rx, (char*) buffer);
	//	HAL_UART_Transmit(&huart5, (uint8_t*) &"RX::", 4, 100);
	//	HAL_UART_Transmit(&huart5, rx, 20, 100);
	return rx;
}
char *GSM_char(char *buff, uint8_t*command) {
	char buffer[150];
//	unsigned short int j = 0;
	for (int i = 0; i < sizeof(buffer); i++)
		buffer[i] = 0;
	uint8_t dummy_read[150] = { 0 };
	while (HAL_UART_DeInit(&huart1))
		;
	while (HAL_UART_Init(&huart1))
		;
	HAL_UART_Receive(&huart1, (uint8_t*) &dummy_read, sizeof(dummy_read), 1000);
	HAL_UART_Transmit(&huart1, (uint8_t*) command, strlen((char*) command),
			100);
	HAL_UART_Receive(&huart1, (uint8_t*) buffer, sizeof(buffer), 2000);

//	 HAL_UART_Transmit(&huart5, (uint8_t*) &"buffer:", 7, 100);
//	 HAL_UART_Transmit(&huart5, (uint8_t*) &buffer, sizeof(buffer), 100);
//	 HAL_UART_Transmit(&huart5, (uint8_t*) &"\r\n", 2, 100);
	//uint8_t *rx = &buffer;
//HAL_UART_Transmit(&huart5, rx, 20, 100);
//	for (int i = 0; i < strlen(buffer); i++) {
//		if (buffer[i] != '\r' && buffer[i] != '\n') {
//			buff[j] = buffer[i];
//			j++;
//		}

//	}
	strcpy(buff, buffer);
//	HAL_UART_Transmit(&huart5, (uint8_t*) &"buff:", 5, 100);
//	 HAL_UART_Transmit(&huart5, (uint8_t*) &buff, sizeof(buff), 100);
//	 HAL_UART_Transmit(&huart5, (uint8_t*) &"\r\n", 2, 100);
	return buff;
}
char *uinque_id() {
	char test[50];
	unsigned short int j = 0;
	for (int i = 0; i < sizeof(test); i++)
		test[i] = 0;
	GSM_char(test, (uint8_t*) &"AT+GSN\r");

//	HAL_UART_Transmit(&huart5, (uint8_t*) &"buff:", 5, 100);
//	HAL_UART_Transmit(&huart5, (uint8_t*) &test, sizeof(test), 1000);
//	HAL_UART_Transmit(&huart5, (uint8_t*) &"\r\n", 2, 100);

	for (int i = 0; i < sizeof(UNIQUE_ID); i++)
		UNIQUE_ID[i] = 0;
//	test = test + 2;
	for (int i = 0; i < strlen(test); i++) {
		if (test[i] != 'O' && test[i] != 'K' && test[i] != '\r'
				&& test[i] != '\n' && test[i] != 'A' && test[i] != 'T'
				&& test[i] != '+' && test[i] != 'G' && test[i] != 'S'
				&& test[i] != 'N' && test[i] != 32) {
			UNIQUE_ID[j] = test[i];
			j++;
		}
	}
//	HAL_UART_Transmit(&huart5, (uint8_t*) &"buff:", 5, 100);
//	HAL_UART_Transmit(&huart5, (uint8_t*) &UNIQUE_ID, sizeof(UNIQUE_ID), 1000);
//	HAL_UART_Transmit(&huart5, (uint8_t*) &"\r\n", 2, 100);
	char *ptr;
//	UNIQUE_ID[strlen(UNIQUE_ID) + 1] = '\0';
	ptr = UNIQUE_ID;
	return ptr;
}
bool sim_registration() {
	uint8_t *helo = GSM_command((uint8_t*) &"at+creg?\r");
	if (strstr((char*) helo, "+CREG: 0,1")
			|| strstr((char*) helo, "+CREG: 0,5")) {
		//HAL_UART_Transmit(&huart5, (uint8_t*) &"register\r\n", 10, 100);
		return true;
	} else {
		//HAL_UART_Transmit(&huart5, (uint8_t*) &"not_reg\r\n", 9, 100);
		return false;
	}
}

bool MOB_number() {
	unsigned short int error_count = 0, j = 0, coma = 0;
	char number[50];
	retry: //HAL_UART_Transmit(&huart5, (uint8_t*) &"GETTING_MOB_NUMBER\r\n", 20,			100);
	for (int i = 0; i < sizeof(number); i++)
		number[i] = 0;
	GSM_char(number, (uint8_t*) &"AT+CPBR=1\r");
	for (int i = 0; i < sizeof(APN); i++)
		APN[i] = 0;
	for (int i = 0; i < sizeof(MOB_NUMBER); i++)
		MOB_NUMBER[i] = 0;
	if ((!strstr(number, "ERROR")) && (strstr(number, "+CPBR"))) {
//		number = number + 12;
		for (int i = 9; i < strlen(number); i++) {
			if ((number[i] != '\n') && (number[i] != '\r') && (number[i] != '"')
					&& (number[i] != 'O') && (number[i] != 'K')
					&& (number[i] != 32)) {
				if (coma == 1) {
					MOB_NUMBER[j] = number[i];
					j++;
				} else if (coma == 3) {
					APN[j] = number[i];
					j++;
				}
			} else if (number[i] != ',') {
				coma++;
				j = 0;
			}
		}
//		number = number + 7;
//		for (int i = 0;
//				(*number != '\n') && (*number != '\r') && (*number != '"');
//				i++) {
//			APN[i] = *number;
//			number++;
//		}
//		return true;
	} else {
		error_count++;
		if (error_count < 2) {
			goto retry;
		}
		/*if (strlen(MOB_NUMBER) != 10 && strlen(MOB_NUMBER) != 13) {
		 strcpy(MOB_NUMBER, "9999999999");
		 }
		 if (!strstr(APN, "airtelgprs.com") && !strstr(APN, "iot.com")
		 && !strstr(APN, "internet") && !strstr(APN, "www")
		 && !strstr(APN, "rcomnet") && !strstr(APN, "bsnlnet")
		 && !strstr(APN, "airteliot.com")) {
		 strcpy(APN, "airtelgprs.com");
		 apn_manual = true;

		 } else
		 apn_manual = false;
		 return false;*/
	}
	if (strlen(MOB_NUMBER) != 10 && strlen(MOB_NUMBER) != 13) {
		strcpy(MOB_NUMBER, "9999999999");
	}
	if (!strstr(APN, "airtelgprs.com") && !strstr(APN, "iot.com")
			&& !strstr(APN, "internet") && !strstr(APN, "www")
			&& !strstr(APN, "rcomnet") && !strstr(APN, "bsnlnet")) {
		strcpy(APN, "airtelgprs.com");
		apn_manual = true;

	} else
		apn_manual = false;
	if (error_count > 2) {
		return false;
		error_count = 0;
	} else
		return true;
}
void sim_number() {
	unsigned short int count = 0, j = 0;
	char number[50];
	sim_no: for (int i = 0; i < sizeof(SIM_NUMBER); i++)
		SIM_NUMBER[i] = 0;
	for (int i = 0; i < sizeof(number); i++)
		number[i] = 0;
	GSM_char(number, (uint8_t*) &"AT+CCID\r");
	if (!strstr(number, "ERROR")) {
//		number = number + 2;
		for (int i = 9; i < strlen(number); i++) {
			if ((number[i] != '\n') && (number[i] != '\r') && (number[i] != 'O')
					&& (number[i] != 'K') && (number[i] != 32)) {
				SIM_NUMBER[j] = number[i];
				j++;
			}
		}
	} else {
		count++;
		if (count < 2) {
			goto sim_no;
		} else
			strcpy(SIM_NUMBER, "99999999999999999999");
	}
}
int signal_quality() {
//	char strength[2];
	unsigned short int err_cnt = 0, j = 0;
	sig_strength: //HAL_UART_Transmit(&huart5, (uint8_t*) &"signal_quality\r\n", 16, 100);
	signal_strength[0] = '\0';
	signal_strength[1] = '\0';
	signal_strength[2] = '\0';
	char number[50];
	GSM_char(number, (uint8_t*) &"AT+CSQ\r");
	if (strstr(number, "+CSQ:")) {
		for (int i = 0; i < strlen(number); i++) {
			if (number[i] != '\r' && number[i] != '\n' && number[i] != '+'
					&& number[i] != 'C' && number[i] != 'S' && number[i] != 'Q'
					&& number[i] != ':' && number[i] != ','
					&& number[i] != 32) {
				signal_strength[j] = number[i];
				j++;
			} else if (number[i] == ',')
				break;
		}
	} else {
		err_cnt++;
		if (err_cnt < 1)
			goto sig_strength;
		strcpy(signal_strength, "00");
	}
//	HAL_UART_Transmit(&huart5, (uint8_t*) &signal_strength,
//			sizeof(signal_strength), 100);
//	HAL_UART_Transmit(&huart5, (uint8_t*) &"\r\n", 2, 10);
	return (atoi(signal_strength));
}
bool enable_time() {
	char get[50];
	times: GSM_char(get, (uint8_t*) &"AT+CTZU?\r");
//time = time + 10;
	if (strstr(get, "+CTZU: 0")) {
		for (int i = 0; i < sizeof(get); i++)
			get[i] = 0;
		GSM_char(get, (uint8_t*) &"AT+CTZU=1\r");
		if (strstr(get, "OK")) {
//			GSM_char(get, (uint8_t*) &"AT+CFUN=1,1\r");
			return true;
		} else {
			for (int i = 0; i < sizeof(get); i++)
				get[i] = 0;
			goto times;
		}
	} else
		return true;

}
char *get_time(char *buff) {
//uint8_t *time1;
	unsigned short int test = 0, j = 0;
	char dat_time[13], time1[50];
	time: for (int i = 0; i < sizeof(clocks); i++)
		clocks[i] = 0;
	for (int i = 0; i < sizeof(time1); i++)
		time1[i] = 0;
//time:// retry method

	GSM_char(time1, (uint8_t*) &"AT+CCLK?\r");
	if (!strstr(time1, "+CCLK:")) {
//		HAL_UART_Transmit(&huart5, (uint8_t*) "wrong\r\n", 7, 100);
		test++;
		if (test < 3)
			goto time;
		else
			strcpy(dat_time, "000000000000");
	} else {
//		HAL_UART_Transmit(&huart5, (uint8_t*) "corect\r\n", 8, 100);
		for (int i = 10; i < strlen(time1); i++) {
			if ((time1[i] != '\n') && (time1[i] != '\r') && (time1[i] != 'O')
					&& (time1[i] != 'K')) {
				if ((time1[i] != '/') && (time1[i] != ',') && (time1[i] != ':')
						&& (time1[i] != '+') && (time1[i] != '"')
						&& (time1[i] != 32)) {
					clocks[j] = time1[i];
					j++;
				} else if ((time1[i] == '+'))
					break;

			}

		}

		dat_time[0] = clocks[4];
		dat_time[1] = clocks[5];
		dat_time[2] = clocks[2];
		dat_time[3] = clocks[3];
		dat_time[4] = clocks[0];
		dat_time[5] = clocks[1];

		for (int i = 6; i < 12; i++) {
			dat_time[i] = clocks[i];
		}
		dat_time[12] = '\0';
	}
//	char *clk; // = malloc(strlen(dat_time));
//	clk = dat_time;
	strcpy(buff, dat_time);
//	HAL_UART_Transmit(&huart5, (uint8_t*) dat_time, strlen(dat_time), 100);
//	HAL_UART_Transmit(&huart5, (uint8_t*) "\r\n", 2, 100);
	return (buff);
}
bool attach_GPRS(char *VPN) {
	unsigned int error_count = 0;
	uint8_t *number;
	for (int i = 0; i < sizeof(DUMMY_RECEIVE); i++)
		DUMMY_RECEIVE[i] = 0;
	label: //HAL_UART_Transmit(&huart5, (uint8_t*) &"GPRS-ATTACHING\r\n", 16,			100);
	number = GSM_command((uint8_t*) &"AT+CGATT=1\r");
	if (strstr((char*) number, "OK")) {
//		HAL_UART_Transmit(&huart5, (uint8_t*) &"GPRS-ATTACHED\r\n", 15, 100);
//		return true;
	} else {
//		HAL_UART_Transmit(&huart5, (uint8_t*) &"GPRS-NOT_ATTACHED\r\n", 19,100);
		error_count++;
		if (error_count > 2)
			return false;
		else
			goto label;
	}
	error_count = 0;
//CSTT:// HAL_UART_Transmit(&huart5, (uint8_t*) &"APN-ATTACHING\r\n", 15, 100);
	char APNS[32];
	CSTT: strcpy(APNS, "AT+CGSOCKCONT=1,\"IP\",\"");
	strcat(APNS, VPN);
	strcat(APNS, "\"\r");
//HAL_UART_Transmit(&huart5, (uint8_t*) &APNS, strlen(APNS), 100);
//HAL_UART_Transmit(&huart5, (uint8_t*) &"\r\n", 2, 10);
	uint8_t *number1 = GSM_command((uint8_t*) &APNS);
	if (strstr((char*) number1, "OK")) {
//HAL_UART_Transmit(&huart5, (uint8_t*) &"APN-ATTACHED\r\n", 14, 100);
//return true;
	} else {
//HAL_UART_Transmit(&huart5, (uint8_t*) &"APN-NOT_ATTACHED\r\n", 18, 100);
		error_count++;
		if (error_count > 2)
			return false;
		else
			goto CSTT;
	}
	error_count = 0;
//wireless: HAL_UART_Transmit(&huart5, (uint8_t*) &"WIRELESS-ATTACHING\r\n",			20, 100);
	uint8_t *number2;
	wireless: number2 = GSM_command((uint8_t*) &"AT+NETOPEN\r");
	if ((strstr((char*) number2, "OK") && strstr((char*) number2, "+NETOPEN: 0"))
			|| strstr((char*) number2, "Network is already opened")) {
		HAL_UART_Transmit(&huart5, (uint8_t*) &"WIRELESS-ATTACHED\r\n", 19,
				100);
//		return true;
	} else {
		HAL_UART_Transmit(&huart5, (uint8_t*) &"WIRELESS-NOT_ATTACHED\r\n", 23,
				100);
		error_count++;
		if (error_count > 2)
			return false;
		else
			goto wireless;
	}
	error_count = 0;
//CIFSR: HAL_UART_Transmit(&huart5, (uint8_t*) &"IP-GETTING\r\n", 12, 100);
	unsigned int dot_count = 0;
	char number3[50];
	CIFSR: for (int i = 0; i < sizeof(number3); i++)
		number3[i] = 0;
	GSM_char(number3, (uint8_t*) &"AT+IPADDR\r");

	for (int i = 10; i < strlen(number3); i++) {
		if (number3[i] == '.')
			dot_count++;
	}
	HAL_UART_Transmit(&huart1, (uint8_t*) "AT+CIPSRIP=0\r", 13, 100);
	HAL_UART_Receive(&huart1, (uint8_t*) DUMMY_RECEIVE, sizeof(DUMMY_RECEIVE),
			1000);
	HAL_UART_Transmit(&huart1, (uint8_t*) "AT+CIPHEAD=0\r", 13, 100);
	HAL_UART_Receive(&huart1, (uint8_t*) DUMMY_RECEIVE, sizeof(DUMMY_RECEIVE),
			1000);
	if (dot_count > 2) {
		HAL_UART_Transmit(&huart5, (uint8_t*) &"IP-ASSIGNED\r\n", 13, 100);
		return true;
	} else {
		HAL_UART_Transmit(&huart5, (uint8_t*) &"IP-NOT_ASSIGNED\r\n", 17, 100);
		error_count++;
		if (error_count > 2)
			return false;
		else
			goto CIFSR;
	}
}

bool get_config() {
	unsigned int count = 0;
//CONFIG: HAL_UART_Transmit(&huart5,
//		(uint8_t*) &"GETTING_CONFIG_FROM_SERVER>>\r\n", 30, 100);.
//	for (int i = 0; i < sizeof(DUMMY_RECEIVE); i++)
//		DUMMY_RECEIVE[i] = 0;
	uint8_t *number3;
	CONFIG: number3 = GSM_command(
			(uint8_t*) &"AT+CIPOPEN=0,\"TCP\",\"159.65.8.242\",5632\r");
	if (strstr((char*) number3, "+CIPOPEN: 0,0")
			|| strstr((char*) number3, "+CIPOPEN: 0,4"))
		;

//	return true;
	else {
		count++;
		if (count > 2)
			return false;
		else {
//			*number3 = '\0';
			goto CONFIG;
		}
	}
	count = 0;
//	CONFIG1: HAL_UART_Transmit(&huart5, (uint8_t*) &"GETTING_RESPONSE\r\n", 18,			100);

	uint8_t *number4;
	CONFIG1: number4 = GSM_command((uint8_t*) &"AT+CIPSEND=0,\r");
	if (strstr((char*) number4, "ERROR")) {
		count++;
		if (count > 3)
			return false;
		else {
//			*number4 = '\0';
			goto CONFIG1;
		}
	} else {
		char termination[] = { 0x1A, 0x0D, 0x0A, 0x00 };
		for (int i = 0; i < sizeof(CONFIG_DATA); i++)
			CONFIG_DATA[i] = 0;
//		char config_port[50];
//		strcpy(config_port,"GET /cgi-bin/config.pl?d=");
//		strcat(config_port,UNIQUE_ID);
//		strcat(config_port,"\r\n");
		HAL_UART_Transmit(&huart1, (uint8_t*) &"GET /cgi-bin/config.pl?d=", 25,
				100);
		HAL_UART_Transmit(&huart1, (uint8_t*) &UNIQUE_ID, strlen(UNIQUE_ID),
				100);
		HAL_UART_Transmit(&huart1, (uint8_t*) &"\r\n", 2, 10);
		HAL_UART_Transmit(&huart1, (uint8_t*) &termination, sizeof(termination),
				10);
//HAL_UART_Transmit(&huart1, (uint8_t*) &"AT+CIPCLOSE\r", 12, 1000);
//		HAL_UART_Receive(&huart1, (uint8_t*) &DUMMY_RECEIVE,
//				sizeof(DUMMY_RECEIVE), 1000);

		HAL_UART_Receive(&huart1, (uint8_t*) &CONFIG_DATA, sizeof(CONFIG_DATA),
				5000);
//		HAL_UART_Receive(&huart1, (uint8_t*) &CONFIG_DATA, sizeof(CONFIG_DATA),
//				6000);
//		HAL_UART_Transmit(&huart5, (uint8_t*) &CONFIG_DATA, strlen(CONFIG_DATA),100);
//		HAL_UART_Transmit(&huart5, (uint8_t*) &"\r\n", 2, 10);
		if (strstr(CONFIG_DATA, "CFG_"))
			return true;
		else
			return false;
	}
}
bool server_response(uint8_t * IP, uint8_t *data) {
	char assing_ip[100], ip3[100], get_ip1[100];
	unsigned short int count = 0, j = 0, coma_count = 0;
	for (int i = 0; i < sizeof(SERVER_RESPONSE); i++)
		SERVER_RESPONSE[i] = 0;
	get_ip: for (int i = 0; i < sizeof(ip2); i++)
		ip2[i] = 0;
	j = 0;
	coma_count = 0;
	for (int i = 0; i < sizeof(assing_ip); i++)
		assing_ip[i] = 0;
	for (int i = 0; i < sizeof(ip3); i++)
		ip3[i] = 0;
	for (int i = 0; i < sizeof(get_ip1); i++)
		get_ip1[i] = 0;
	strcpy(ip3, "AT+CDNSGIP=\"");
	strcat(ip3, (const char*) IP);
	strcat(ip3, "\"\r");
//	HAL_UART_Transmit(&huart5, (uint8_t*) " ip3:", 5, 100);
//	HAL_UART_Transmit(&huart5, (uint8_t*) ip3, sizeof(ip3), 1000);
//	HAL_UART_Transmit(&huart5, (uint8_t*) "\r\n", 2, 10);

	GSM_char(assing_ip, (uint8_t*) ip3);
	if (strstr(assing_ip, "+CDNSGIP: 1,")) {
		for (int i = 0; i < strlen(assing_ip); i++) {
			if (assing_ip[i] != '\r' && assing_ip[i] != '\n'
					&& assing_ip[i] != 32) {
				if (assing_ip[i] == ',')
					coma_count++;
				if (coma_count == 2) {
					if (assing_ip[i] != 'O' && assing_ip[i] != 'K'
							&& assing_ip[i] != '"' && assing_ip[i] != ',') {
						get_ip1[j] = assing_ip[i];
						j++;
					}
				}

			}
		}
	} else {
		count++;
		if (count < 3)
			goto get_ip;
		else
			return false;
	}
//	HAL_UART_Transmit(&huart5, (uint8_t *) "GET_ip1:", 8, 100);
//	HAL_UART_Transmit(&huart5, (uint8_t *) &get_ip1, strlen(get_ip1), 1000);
//	HAL_UART_Transmit(&huart5, (uint8_t*) &"\r\n", 2, 10);

//RESPONSE1: HAL_UART_Transmit(&huart5, (uint8_t*) &"GETTING_RESPONSE\r\n",			18, 100);
//	GSM_char(assing_ip, (uint8_t*) ip3);
	strcpy(ip2, "AT+CIPOPEN=0,\"TCP\",\"");
	strcat(ip2, get_ip1);
	strcat(ip2, "\",5632\r");
//	HAL_UART_Transmit(&huart5, (uint8_t *) "ip2:", 3, 100);
//	HAL_UART_Transmit(&huart5, (uint8_t *) &ip2, strlen(ip2), 1000);
//	HAL_UART_Transmit(&huart5, (uint8_t*) &"\r\n", 2, 10);
//memset(start, 0, sizeof(start));
//	GSM_char(start, (uint8_t*) ip2);
	uint8_t * start;
	RESPONSE1: start = GSM_command((uint8_t*) ip2);
//	HAL_UART_Transmit(&huart5, (uint8_t*) "SERVER_RESPONSE:", 16, 1000);
//	HAL_UART_Transmit(&huart5, (uint8_t*) &start, strlen((char*) start), 1000);
//	RESPONSE1: HAL_UART_Receive(&huart1, (uint8_t*) &DUMMY_RECEIVE,
//			sizeof(DUMMY_RECEIVE), 1000);
//	RESPONSE1:HAL_UART_Transmit(&huart1, (uint8_t*) &ip2, strlen(ip2), 1000);
//
//	HAL_UART_Receive(&huart1, (uint8_t*) buffer, sizeof(buffer), 2000);
//	HAL_UART_Transmit(&huart5, (uint8_t*) "buffer:", 7, 7);
//	HAL_UART_Transmit(&huart5, (uint8_t*) buffer, sizeof(buffer), 1000);

	if (strstr((char*) start, "+CIPOPEN: 0,0")
			|| strstr((char*) start, "+CIPOPEN: 0,4"))
			//if (strstr(start, "OK"))
					{
//HAL_UART_Transmit(&huart5, (uint8_t*) "OK\r\n", 4, 7);
	} else {
		response_retry++;
		if (response_retry > 2)
			return false;
		else {
			//	*start = '\0';
//			strcpy(buffer, "\0");	//memset(buffer, 0, sizeof(buffer));
//			for (int i = 0; i < sizeof(buffer); i++)
//				buffer[i] = 0;
//			for (int i = 0; i < sizeof(DUMMY_RECEIVE); i++)
//				DUMMY_RECEIVE[i] = 0;
//			strcpy(DUMMY_RECEIVE, "\0");
			//memset(DUMMY_RECEIVE, 0, sizeof(DUMMY_RECEIVE));
			goto RESPONSE1;
		}
	}
	response_retry = 0;
//	for (int i = 0; i < sizeof(buffer); i++)
//		buffer[i] = 0;
//strcpy(buffer, "\0");	//memset(buffer, 0, sizeof(buffer));
//HAL_UART_Transmit(&huart5, (uint8_t*) &"WAITING_RESPONSE\r\n", 18, 100);
	uint8_t *number5;
	RESPONSE2: number5 = GSM_command((uint8_t*) &"AT+CIPSEND=0,\r");
//	RESPONSE2: HAL_UART_Transmit(&huart1, (uint8_t*) &"AT+CIPSEND\r", 11, 100);
// HAL_UART_Receive(&huart1, (uint8_t*) &buffer, sizeof(buffer), 1000);
// HAL_UART_Transmit(&huart5, (uint8_t*) &"buffer:", 7, 100);
// HAL_UART_Transmit(&huart5, (uint8_t*) &buffer, strlen(buffer), 100);
	if (strstr((char*) number5, "ERROR")) {
		response_retry++;
		if (response_retry > 2)
			return false;
		else {
			for (int i = 0; i < sizeof(buffer); i++)
				buffer[i] = 0;
			goto RESPONSE2;
		}
	} else {
		char cntl[] = { 0x1A, 0x0D, 0x0A, 0x00 };
//HAL_UART_Transmit(&huart1, (uint8_t*) VERSION, strlen((char*) VERSION),		500);
//	HAL_UART_Transmit(&huart1, (uint8_t*) DEVICE_ID,strlen((char*) DEVICE_ID), 500);
		HAL_UART_Transmit(&huart1, (uint8_t*) data, strlen((char*) data), 1500);
		HAL_UART_Transmit(&huart1, (uint8_t*) &"\r\n", 2, 10);
		HAL_UART_Transmit(&huart1, (uint8_t*) &cntl, sizeof(cntl), 100);
//		HAL_UART_Transmit(&huart1, (uint8_t*) &"AT+CIPCLOSE\r", 12, 1000);

		HAL_UART_Receive(&huart1, (uint8_t*) &SERVER_RESPONSE,
				sizeof(SERVER_RESPONSE), 7000);

//		HAL_UART_Transmit(&huart5, (uint8_t*) &"\r\nSERVER_RESPONSE:", 18, 100);
//		HAL_UART_Transmit(&huart5, (uint8_t*) &SERVER_RESPONSE,
//				strlen(SERVER_RESPONSE), 1000);
//		HAL_UART_Transmit(&huart5, (uint8_t*) &"\r\n", 2, 10);

		response_retry = 0;
//		for (int i = 0; i < sizeof(buffer); i++)
//			buffer[i] = 0;
		HAL_UART_Transmit(&huart1, (uint8_t*) &"AT+CIPCLOSE=0\r", 14, 100);
		HAL_UART_Receive(&huart1, (uint8_t*) &dummy, sizeof(dummy), 100);
		if (strstr(SERVER_RESPONSE, "OK_"))
			return true;
		else
			return false;

	}
//return true;
}
bool GSM_SLEEP_MODE() {
	uint8_t *res;
	res = GSM_command((uint8_t*) &"AT+CFUN=0\r");
	if (strstr((char*) res, "OK")) {
//		uint8_t *res1 = GSM_command((uint8_t*) &"AT+CNETLIGHT=0\r");
//		if (strstr((char*) res1, "OK"))
		return true;
//		else
//			return false;
	} else
		return false;
}
bool SIM_AVAILABLE() {
	uint8_t *res1;
	res1 = GSM_command((uint8_t*) &"AT+CSPN?\r");
	if (!strstr((char*) res1, "ERROR"))
		return true;
	else
		return false;
//	if (strstr((char*) res1, "+CSPN: \"airtel\",1")
//			|| strstr((char*) res1, "+CSPN: \"airtel\",0"))
//		return true;
//	else
//		return false;
}
//************ GSM_PHONE_BOOK_WRITE*****************//

//	char testing[100];
//	HAL_UART_Transmit(&huart1,
//			(uint8_t*) &"AT+CPBW=1,\"7094467601\",129,\"iot.com\"\r", 37, 100);
//	HAL_UART_Receive(&huart1, (uint8_t*) &testing, sizeof(testing), 1000);
//	HAL_UART_Transmit(&huart5, (uint8_t*) &testing, sizeof(testing), 1000);
//	HAL_UART_Transmit(&huart5, (uint8_t*) &"\r\n", 2, 10);

