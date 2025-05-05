/*
 * Copyright (c) 2001-2003 Swedish Institute of Computer Science.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. The name of the author may not be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT
 * SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT
 * OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
 * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY
 * OF SUCH DAMAGE.
 *
 * This file is part of the lwIP TCP/IP stack.
 *
 * Author: Adam Dunkels <adam@sics.se>
 *
 */

#include "lwip/opt.h"
#include "event_groups.h"

#define BUFFER_SIZE   (8U)

extern EventGroupHandle_t tcpipEvent;
extern EventBits_t tcpipBits;
extern QueueHandle_t RFID_queue;
extern QueueHandle_t servo_queue;

char UID_string[BUFFER_SIZE] = {0U};

#if LWIP_NETCONN

#include "lwip/sys.h"
#include "lwip/api.h"
/*-----------------------------------------------------------------------------------*/

typedef enum
{
	Authentication = 0U,
	Registration,
	Total
}enConsult;

static u8_t database_consult(u8_t ConsultType)
{

	struct netconn *conn;
	err_t err;
	int result;
	char* charptr;
	ip4_addr_t ipaddr;
	char HTTPrequest[100] = {0};
	struct netbuf *buf;
	void *data;
	u16_t len;
	u8_t FoundState = 0U;

	/* Create a new connection identifier. */
	/* Bind connection to well known port number 1031. */
	conn = netconn_new(NETCONN_TCP);
	netconn_bind(conn, IP_ADDR_ANY, 7);

	LWIP_ERROR("tcpecho: invalid conn", (conn != NULL), return;);

	IP4_ADDR(&ipaddr, 192,168,1,2);
	netconn_connect(conn, &ipaddr, 1031);

	if(ConsultType == Authentication)
	{
		//PRINTF("Authenticate user\n\r");
		//authenticate user
		sprintf(HTTPrequest, "GET /nfcauth.php?tagid=%s HTTP/1.0\r\n\r\n", UID_string);
		err = netconn_write(conn, HTTPrequest, strlen(HTTPrequest), NETCONN_COPY);
		while ((err = netconn_recv(conn, &buf)) == ERR_OK)
		{
			do {
				netbuf_data(buf, &data, &len);
				PRINTF("Received: %s\n", data);
			} while (netbuf_next(buf) >= 0);
			//PRINTF("Received: %s\n", data);
			charptr = strstr((const char *)data, "tag_id: 41e527a"); //tag_id: 4474c7a1e4e81
			if (charptr)
			{
				PRINTF("User exists\n");
				FoundState = 1U;
			}
			netbuf_delete(buf);
		}
	}
	else if(ConsultType == Registration)
	{
		PRINTF("Register new user\n\r");
		//register new user
		sprintf(HTTPrequest, "GET /nfcreg.php?tagid=%s&name=HM&lastname=HV&access=Mortal HTTP/1.0\r\n\r\n", UID_string);
		err = netconn_write(conn, HTTPrequest, strlen(HTTPrequest), NETCONN_COPY);
		while ((err = netconn_recv(conn, &buf)) == ERR_OK)
		{
			do {
				netbuf_data(buf, &data, &len);
				PRINTF("Received: %s\n", data);
			} while (netbuf_next(buf) >= 0);
			//PRINTF("Received: %s\n", data);
			result = strncmp("HTTP/1.1 200 OK", data, 15);
			if (result == 0)
			{
				PRINTF("User Registered\n");
			}
			netbuf_delete(buf);
		}
	}

	netconn_close(conn);
	netconn_delete(conn);

	return FoundState;
}




void database_task(void *pvParameters)
{
	u8_t Authenticator = 0U;

	//Wait until TCPIP stack is up and running
	tcpipBits = xEventGroupWaitBits(
					tcpipEvent,    /* The event group being tested. */
					0b1,           /* The bit within the event group to wait for: bit 0. */
					pdFALSE,       /* BIT 0 should NOT be cleared before returning. */
					pdFALSE,       /* Don't wait for both bits, either bit will do. */
					portMAX_DELAY);/* Wait a maximum of 100ms for either bit to be set. */

	while(1)
	{
		if (xQueueReceive(RFID_queue, UID_string, portMAX_DELAY) == pdTRUE)
		{

			/*Registro de nuevo RFID Tag*/
	//		Authenticator = database_consult(Authentication);
	//
	//		if(Authenticator == 0U)
	//		{
	//			(void)database_consult(Registration);
	//		}
	//		else
	//		{
	//			/*Usuario ya existente*/
	//		}

			/*Accionar SmartLock*/
			Authenticator = database_consult(Authentication);

			if(Authenticator)
			{
				xQueueSend(servo_queue, "o" ,0);
			}
			else
			{
				/*Usuario no registrado*/
			}


		//Test from the web browser
		//http://10.215.170.119:1031/datalog.php?frdm_id=FRMD-Profe&sensor=acc&data=123123
		//http://10.215.170.119:1031/nfcauth.php?tagid=4474c7a1e4e81
		//http://10.215.170.119:1031/nfcreg.php?tagid=4474c7a1e4e81&name=Luis&lastname=Garabito&access=Mortal
		//Test from the web browser

		//sprintf(HTTPrequest, "GET /nfcauth.php?tagid=%s HTTP/1.0\r\n\r\n", TagUIDstr);
		//netconn_write(conn, HTTPrequest,strlen(HTTPrequest),NETCONN_COPY);

		//PRINTF("Sensor data Logged\n\r");
		//datalog sensor
	//	sprintf(HTTPrequest, "GET /datalog.php?frdm_id=Iteso&sensor=LightSensor&data=%d HTTP/1.0\r\n\r\n", 508353);
	//	err = netconn_write(conn, HTTPrequest, strlen(HTTPrequest), NETCONN_COPY);
	//	while ((err = netconn_recv(conn, &buf)) == ERR_OK)
	//	{
	//		do {
	//			netbuf_data(buf, &data, &len);
	//			PRINTF("Received: %s\n", data);
	//		} while (netbuf_next(buf) >= 0);
	//		//PRINTF("Received: %s\n", data);
	//		result = strncmp("HTTP/1.1 200 OK", data, 15);
	//		if (result == 0)
	//		{
	//			PRINTF("Data logged\n");
	//		}
	//		netbuf_delete(buf);
	//	}
		}

//		vTaskSuspend(NULL);
	}

}
/*-----------------------------------------------------------------------------------*/

#endif /* LWIP_NETCONN */

