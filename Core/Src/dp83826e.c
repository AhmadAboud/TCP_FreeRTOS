/*
 * dp83826e.c
 *
 *  Created on: 08.05.2023
 *      Author: sven.bergmann
 */

/* Includes ------------------------------------------------------------------*/
#include "stm32h7xx_hal.h"


#include "dp83826e.h"

/** @addtogroup BSP
  * @{
  */

/** @addtogroup Component
  * @{
  */

/** @defgroup DP83826E DP83826E
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/** @defgroup DP83826E_Private_Defines DP83826E Private Defines
  * @{
  */
#define DP83826E_SW_RESET_TO    ((uint32_t)500U)
#define DP83826E_INIT_TO        ((uint32_t)2000U)
#define DP83826E_MAX_DEV_ADDR   ((uint32_t)31U)
/**
  * @}
  */

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/** @defgroup DP83826E_Private_Functions DP83826E Private Functions
  * @{
  */

/**
  * @brief  Register IO functions to component object
  * @param  pObj: device object  of DP83826E_Object_t.
  * @param  ioctx: holds device IO functions.
  * @retval DP83826E_STATUS_OK  if OK
  *         DP83826E_STATUS_ERROR if missing mandatory function
  */
int32_t  DP83826E_RegisterBusIO(dp83826e_Object_t *pObj, dp83826e_IOCtx_t *ioctx)
{
  if(!pObj || !ioctx->ReadReg || !ioctx->WriteReg || !ioctx->GetTick)
  {
    return DP83826E_STATUS_ERROR;
  }

  pObj->IO.Init = ioctx->Init;
  pObj->IO.DeInit = ioctx->DeInit;
  pObj->IO.ReadReg = ioctx->ReadReg;
  pObj->IO.WriteReg = ioctx->WriteReg;
  pObj->IO.GetTick = ioctx->GetTick;

  return DP83826E_STATUS_OK;
}



int32_t DP83826E_FindFirstPHY(dp83826e_Object_t *pObj)
{
	uint32_t regvalue = 0, addr = 0;
	int32_t status = DP83826E_STATUS_OK;
	/* for later check */
	     pObj->DevAddr = DP83826E_MAX_DEV_ADDR + 1;

	     /* Get the device address from special mode register */
	     for(addr = 0; addr <= DP83826E_MAX_DEV_ADDR; addr ++)
	     {
	       if(pObj->IO.ReadReg(addr, DP83826E_PHYCR, &regvalue) < 0)
	       {
	         status = DP83826E_STATUS_READ_ERROR;
	         /* Can't read from this device address
	            continue with next address */
	         continue;
	       }

	       if((regvalue & DP83826E_PHYCR_PHY_ADDR) == addr)
	       {
	         pObj->DevAddr = addr;
	         status = DP83826E_STATUS_OK;
	         break;
	       }
	     }

	     if(pObj->DevAddr > DP83826E_MAX_DEV_ADDR)
	     {
	       status = DP83826E_STATUS_ADDRESS_ERROR;
	     }

    return status;
}

int32_t DP83826E_SoftwareReset(dp83826e_Object_t *pObj)
{
	uint32_t tickstart = 0, regvalue = 0;
	int32_t status = DP83826E_STATUS_OK;
	/* set a software reset  */
		if(pObj->IO.WriteReg(pObj->DevAddr, DP83826E_BCR, DP83826E_BCR_SOFT_RESET) >= 0)
		{
			/* get software reset status */
			if(pObj->IO.ReadReg(pObj->DevAddr, DP83826E_BCR, &regvalue) >= 0)
			{
				tickstart = pObj->IO.GetTick();
				while ((regvalue & DP83826E_BCR_SOFT_RESET) == DP83826E_BCR_SOFT_RESET)
				{
					if(pObj->IO.ReadReg(pObj->DevAddr, DP83826E_BCR, &regvalue) < 0)
					{
						status = DP83826E_STATUS_READ_ERROR;
						break;
					}
					else if ((pObj->IO.GetTick() - tickstart) >= DP83826E_SW_RESET_TO)
					{
						status = DP83826E_STATUS_RESET_TIMEOUT;
						break;
					}
				}
			}
			else
			{
				status = DP83826E_STATUS_WRITE_ERROR;
			}
		}
		else
		{
			status = DP83826E_STATUS_READ_ERROR;
		}

    return status;

}

int32_t DP83826E_Configure(dp83826e_Object_t *pObj)
{
	int32_t status = DP83826E_STATUS_OK;

	// LED0 (orange) polarität einstellen
	pObj->IO.WriteReg(pObj->DevAddr, DP83826E_LEDCR, DP83826E_LEDCR_CONF);
	// LED1 (grün) polarität einstellen
	pObj->IO.WriteReg(pObj->DevAddr, DP83826E_REGCR, DP83826E_REGCR_FUN_ADR);
	pObj->IO.WriteReg(pObj->DevAddr, DP83826E_ADDAR, DP83826E_LEDCFG2);
	pObj->IO.WriteReg(pObj->DevAddr, DP83826E_REGCR, DP83826E_REGCR_FUN_DATA);
	pObj->IO.WriteReg(pObj->DevAddr, DP83826E_ADDAR, DP83826E_LEDCFG2_CONF);


	//pObj->IO.WriteReg(pObj->DevAddr, DP83826E_REGCR, DP83826E_REGCR_FUN_ADR);
	//pObj->IO.WriteReg(pObj->DevAddr, DP83826E_ADDAR, ((uint16_t)0x0468U));
	//pObj->IO.WriteReg(pObj->DevAddr, DP83826E_REGCR, DP83826E_REGCR_FUN_DATA);
	//pObj->IO.ReadReg(pObj->DevAddr, DP83826E_ADDAR, &regvalue);

    return status;
}

/**
  * @brief  Initialize the dp83826e and configure the needed hardware resources
  * @param  pObj: device object DP83826E_Object_t.
  * @retval DP83826E_STATUS_OK  if OK
  *         DP83826E_STATUS_ADDRESS_ERROR if cannot find device address
  *         DP83826E_STATUS_READ_ERROR if connot read register
  *         DP83826E_STATUS_WRITE_ERROR if connot write to register
  *         DP83826E_STATUS_RESET_TIMEOUT if cannot perform a software reset
  */
 int32_t DP83826E_Init(dp83826e_Object_t *pObj)
 {
	 uint32_t tickstart = 0;
	 int32_t status = DP83826E_STATUS_OK;

	if(pObj->Is_Initialized == 0)
	{
		if(pObj->IO.Init != 0)
		{
			/* GPIO and Clocks initialization */
			pObj->IO.Init();
		}

		/* Suche den PHY mit der niedrigsten Adresse */
		status = DP83826E_FindFirstPHY(pObj);
		if (status == DP83826E_STATUS_OK)
		{
			// Einmal resetten
			status = DP83826E_SoftwareReset(pObj);
			if (status == DP83826E_STATUS_OK)
			{
				// und einstellen :)
				status = DP83826E_Configure(pObj);
				if (status == DP83826E_STATUS_OK)
				{
					tickstart = pObj->IO.GetTick();
					while ((pObj->IO.GetTick() - tickstart) <= 2000)
					{
					}
				     pObj->Is_Initialized = 1;
				}
			}
		}
	}
   return status;
 }

/**
  * @brief  De-Initialize the dp83826e and it's hardware resources
  * @param  pObj: device object DP83826E_Object_t.
  * @retval None
  */
int32_t DP83826E_DeInit(dp83826e_Object_t *pObj)
{
  if(pObj->Is_Initialized)
  {
    if(pObj->IO.DeInit != 0)
    {
      if(pObj->IO.DeInit() < 0)
      {
        return DP83826E_STATUS_ERROR;
      }
    }

    pObj->Is_Initialized = 0;
  }

  return DP83826E_STATUS_OK;
}

/**
  * @brief  Disable the DP83826E power down mode.
  * @param  pObj: device object DP83826E_Object_t.
  * @retval DP83826E_STATUS_OK  if OK
  *         DP83826E_STATUS_READ_ERROR if connot read register
  *         DP83826E_STATUS_WRITE_ERROR if connot write to register
  */
int32_t DP83826E_DisablePowerDownMode(dp83826e_Object_t *pObj)
{
  uint32_t readval = 0;
  int32_t status = DP83826E_STATUS_OK;

  if(pObj->IO.ReadReg(pObj->DevAddr, DP83826E_BCR, &readval) >= 0)
  {
    readval &= ~DP83826E_BCR_POWER_DOWN;

    /* Apply configuration */
    if(pObj->IO.WriteReg(pObj->DevAddr, DP83826E_BCR, readval) < 0)
    {
      status =  DP83826E_STATUS_WRITE_ERROR;
    }
  }
  else
  {
    status = DP83826E_STATUS_READ_ERROR;
  }

  return status;
}

/**
  * @brief  Enable the DP83826E power down mode.
  * @param  pObj: device object DP83826E_Object_t.
  * @retval DP83826E_STATUS_OK  if OK
  *         DP83826E_STATUS_READ_ERROR if connot read register
  *         DP83826E_STATUS_WRITE_ERROR if connot write to register
  */
int32_t DP83826E_EnablePowerDownMode(dp83826e_Object_t *pObj)
{
  uint32_t readval = 0;
  int32_t status = DP83826E_STATUS_OK;

  if(pObj->IO.ReadReg(pObj->DevAddr, DP83826E_BCR, &readval) >= 0)
  {
    readval |= DP83826E_BCR_POWER_DOWN;

    /* Apply configuration */
    if(pObj->IO.WriteReg(pObj->DevAddr, DP83826E_BCR, readval) < 0)
    {
      status =  DP83826E_STATUS_WRITE_ERROR;
    }
  }
  else
  {
    status = DP83826E_STATUS_READ_ERROR;
  }

  return status;
}

/**
  * @brief  Start the auto negotiation process.
  * @param  pObj: device object DP83826E_Object_t.
  * @retval DP83826E_STATUS_OK  if OK
  *         DP83826E_STATUS_READ_ERROR if connot read register
  *         DP83826E_STATUS_WRITE_ERROR if connot write to register
  */
int32_t DP83826E_StartAutoNego(dp83826e_Object_t *pObj)
{
  uint32_t readval = 0;
  int32_t status = DP83826E_STATUS_OK;

  if(pObj->IO.ReadReg(pObj->DevAddr, DP83826E_BCR, &readval) >= 0)
  {
    readval |= DP83826E_BCR_AUTONEGO_EN;

    /* Apply configuration */
    if(pObj->IO.WriteReg(pObj->DevAddr, DP83826E_BCR, readval) < 0)
    {
      status =  DP83826E_STATUS_WRITE_ERROR;
    }
  }
  else
  {
    status = DP83826E_STATUS_READ_ERROR;
  }

  return status;
}

/**
  * @brief  Get the link state of DP83826E device.
  * @param  pObj: Pointer to device object.
  * @param  pLinkState: Pointer to link state
  * @retval DP83826E_STATUS_LINK_DOWN  if link is down
  *         DP83826E_STATUS_AUTONEGO_NOTDONE if Auto nego not completed
  *         DP83826E_STATUS_100MBITS_FULLDUPLEX if 100Mb/s FD
  *         DP83826E_STATUS_100MBITS_HALFDUPLEX if 100Mb/s HD
  *         DP83826E_STATUS_10MBITS_FULLDUPLEX  if 10Mb/s FD
  *         DP83826E_STATUS_10MBITS_HALFDUPLEX  if 10Mb/s HD
  *         DP83826E_STATUS_READ_ERROR if connot read register
  *         DP83826E_STATUS_WRITE_ERROR if connot write to register
  */
int32_t DP83826E_GetLinkState(dp83826e_Object_t *pObj)
{
  uint32_t readval = 0;

  /* Read Status register  */
  if(pObj->IO.ReadReg(pObj->DevAddr, DP83826E_BSR, &readval) < 0)
  {
    return DP83826E_STATUS_READ_ERROR;
  }

  /* Read Status register again */
  if(pObj->IO.ReadReg(pObj->DevAddr, DP83826E_BSR, &readval) < 0)
  {
    return DP83826E_STATUS_READ_ERROR;
  }

  if((readval & DP83826E_BSR_LINK_STATUS) == 0)
  {
    /* Return Link Down status */
    return DP83826E_STATUS_LINK_DOWN;
  }

  /* Check Auto negotiaition */
  if(pObj->IO.ReadReg(pObj->DevAddr, DP83826E_BCR, &readval) < 0)
  {
    return DP83826E_STATUS_READ_ERROR;
  }

  if((readval & DP83826E_BCR_AUTONEGO_EN) != DP83826E_BCR_AUTONEGO_EN)
  {
    if(((readval & DP83826E_BCR_SPEED_SELECT) == DP83826E_BCR_SPEED_SELECT) && ((readval & DP83826E_BCR_DUPLEX_MODE) == DP83826E_BCR_DUPLEX_MODE))
    {
      return DP83826E_STATUS_100MBITS_FULLDUPLEX;
    }
    else if ((readval & DP83826E_BCR_SPEED_SELECT) == DP83826E_BCR_SPEED_SELECT)
    {
      return DP83826E_STATUS_100MBITS_HALFDUPLEX;
    }
    else if ((readval & DP83826E_BCR_DUPLEX_MODE) == DP83826E_BCR_DUPLEX_MODE)
    {
      return DP83826E_STATUS_10MBITS_FULLDUPLEX;
    }
    else
    {
      return DP83826E_STATUS_10MBITS_HALFDUPLEX;
    }
  }
  else /* Auto Nego enabled */
  {
    if(pObj->IO.ReadReg(pObj->DevAddr, DP83826E_BSR, &readval) < 0)
    {
      return DP83826E_STATUS_READ_ERROR;
    }

    /* Check if auto nego not done */
    if((readval & DP83826E_BSR_AUTONEGO_CPLT) == 0)
    {
      return DP83826E_STATUS_AUTONEGO_NOTDONE;
    }
    if(pObj->IO.ReadReg(pObj->DevAddr, ((uint16_t)0x0010U), &readval) < 0)
    {
      return DP83826E_STATUS_READ_ERROR;
    }


    if((readval & DP83826E_PHYSCSR_HCDSPEEDMASK) == DP83826E_PHYSCSR_100BTX_FD)
    {
      return DP83826E_STATUS_100MBITS_FULLDUPLEX;
    }
    else if ((readval & DP83826E_PHYSCSR_HCDSPEEDMASK) == DP83826E_PHYSCSR_100BTX_HD)
    {
      return DP83826E_STATUS_100MBITS_HALFDUPLEX;
    }
    else if ((readval & DP83826E_PHYSCSR_HCDSPEEDMASK) == DP83826E_PHYSCSR_10BT_FD)
    {
      return DP83826E_STATUS_10MBITS_FULLDUPLEX;
    }
    else
    {
      return DP83826E_STATUS_100MBITS_FULLDUPLEX;
    }
  }
}

/**
  * @brief  Set the link state of DP83826E device.
  * @param  pObj: Pointer to device object.
  * @param  pLinkState: link state can be one of the following
  *         DP83826E_STATUS_100MBITS_FULLDUPLEX if 100Mb/s FD
  *         DP83826E_STATUS_100MBITS_HALFDUPLEX if 100Mb/s HD
  *         DP83826E_STATUS_10MBITS_FULLDUPLEX  if 10Mb/s FD
  *         DP83826E_STATUS_10MBITS_HALFDUPLEX  if 10Mb/s HD
  * @retval DP83826E_STATUS_OK  if OK
  *         DP83826E_STATUS_ERROR  if parameter error
  *         DP83826E_STATUS_READ_ERROR if connot read register
  *         DP83826E_STATUS_WRITE_ERROR if connot write to register
  */
int32_t DP83826E_SetLinkState(dp83826e_Object_t *pObj, uint32_t LinkState)
{
  uint32_t bcrvalue = 0;
  int32_t status = DP83826E_STATUS_OK;

  if(pObj->IO.ReadReg(pObj->DevAddr, DP83826E_BCR, &bcrvalue) >= 0)
  {
    /* Disable link config (Auto nego, speed and duplex) */
    bcrvalue &= ~(DP83826E_BCR_AUTONEGO_EN | DP83826E_BCR_SPEED_SELECT | DP83826E_BCR_DUPLEX_MODE);

    if(LinkState == DP83826E_STATUS_100MBITS_FULLDUPLEX)
    {
      bcrvalue |= (DP83826E_BCR_SPEED_SELECT | DP83826E_BCR_DUPLEX_MODE);
    }
    else if (LinkState == DP83826E_STATUS_100MBITS_HALFDUPLEX)
    {
      bcrvalue |= DP83826E_BCR_SPEED_SELECT;
    }
    else if (LinkState == DP83826E_STATUS_10MBITS_FULLDUPLEX)
    {
      bcrvalue |= DP83826E_BCR_DUPLEX_MODE;
    }
    else
    {
      /* Wrong link status parameter */
      status = DP83826E_STATUS_ERROR;
    }
  }
  else
  {
    status = DP83826E_STATUS_READ_ERROR;
  }

  if(status == DP83826E_STATUS_OK)
  {
    /* Apply configuration */
    if(pObj->IO.WriteReg(pObj->DevAddr, DP83826E_BCR, bcrvalue) < 0)
    {
      status = DP83826E_STATUS_WRITE_ERROR;
    }
  }

  return status;
}

/**
  * @brief  Enable loopback mode.
  * @param  pObj: Pointer to device object.
  * @retval DP83826E_STATUS_OK  if OK
  *         DP83826E_STATUS_READ_ERROR if connot read register
  *         DP83826E_STATUS_WRITE_ERROR if connot write to register
  */
int32_t DP83826E_EnableLoopbackMode(dp83826e_Object_t *pObj)
{
  uint32_t readval = 0;
  int32_t status = DP83826E_STATUS_OK;

  if(pObj->IO.ReadReg(pObj->DevAddr, DP83826E_BCR, &readval) >= 0)
  {
    readval |= DP83826E_BCR_LOOPBACK;

    /* Apply configuration */
    if(pObj->IO.WriteReg(pObj->DevAddr, DP83826E_BCR, readval) < 0)
    {
      status = DP83826E_STATUS_WRITE_ERROR;
    }
  }
  else
  {
    status = DP83826E_STATUS_READ_ERROR;
  }

  return status;
}

/**
  * @brief  Disable loopback mode.
  * @param  pObj: Pointer to device object.
  * @retval DP83826E_STATUS_OK  if OK
  *         DP83826E_STATUS_READ_ERROR if connot read register
  *         DP83826E_STATUS_WRITE_ERROR if connot write to register
  */
int32_t DP83826E_DisableLoopbackMode(dp83826e_Object_t *pObj)
{
  uint32_t readval = 0;
  int32_t status = DP83826E_STATUS_OK;

  if(pObj->IO.ReadReg(pObj->DevAddr, DP83826E_BCR, &readval) >= 0)
  {
    readval &= ~DP83826E_BCR_LOOPBACK;

    /* Apply configuration */
    if(pObj->IO.WriteReg(pObj->DevAddr, DP83826E_BCR, readval) < 0)
    {
      status =  DP83826E_STATUS_WRITE_ERROR;
    }
  }
  else
  {
    status = DP83826E_STATUS_READ_ERROR;
  }

  return status;
}

/**
  * @brief  Enable IT source.
  * @param  pObj: Pointer to device object.
  * @param  Interrupt: IT source to be enabled
  *         should be a value or a combination of the following:
  *         DP83826E_WOL_IT
  *         DP83826E_ENERGYON_IT
  *         DP83826E_AUTONEGO_COMPLETE_IT
  *         DP83826E_REMOTE_FAULT_IT
  *         DP83826E_LINK_DOWN_IT
  *         DP83826E_AUTONEGO_LP_ACK_IT
  *         DP83826E_PARALLEL_DETECTION_FAULT_IT
  *         DP83826E_AUTONEGO_PAGE_RECEIVED_IT
  * @retval DP83826E_STATUS_OK  if OK
  *         DP83826E_STATUS_READ_ERROR if connot read register
  *         DP83826E_STATUS_WRITE_ERROR if connot write to register
  */
int32_t DP83826E_EnableIT(dp83826e_Object_t *pObj, uint32_t Interrupt)
{
  uint32_t readval = 0;
  int32_t status = DP83826E_STATUS_OK;

  if(pObj->IO.ReadReg(pObj->DevAddr, DP83826E_IMR, &readval) >= 0)
  {
    readval |= Interrupt;

    /* Apply configuration */
    if(pObj->IO.WriteReg(pObj->DevAddr, DP83826E_IMR, readval) < 0)
    {
      status =  DP83826E_STATUS_WRITE_ERROR;
    }
  }
  else
  {
    status = DP83826E_STATUS_READ_ERROR;
  }

  return status;
}

/**
  * @brief  Disable IT source.
  * @param  pObj: Pointer to device object.
  * @param  Interrupt: IT source to be disabled
  *         should be a value or a combination of the following:
  *         DP83826E_WOL_IT
  *         DP83826E_ENERGYON_IT
  *         DP83826E_AUTONEGO_COMPLETE_IT
  *         DP83826E_REMOTE_FAULT_IT
  *         DP83826E_LINK_DOWN_IT
  *         DP83826E_AUTONEGO_LP_ACK_IT
  *         DP83826E_PARALLEL_DETECTION_FAULT_IT
  *         DP83826E_AUTONEGO_PAGE_RECEIVED_IT
  * @retval DP83826E_STATUS_OK  if OK
  *         DP83826E_STATUS_READ_ERROR if connot read register
  *         DP83826E_STATUS_WRITE_ERROR if connot write to register
  */
int32_t DP83826E_DisableIT(dp83826e_Object_t *pObj, uint32_t Interrupt)
{
  uint32_t readval = 0;
  int32_t status = DP83826E_STATUS_OK;

  if(pObj->IO.ReadReg(pObj->DevAddr, DP83826E_IMR, &readval) >= 0)
  {
    readval &= ~Interrupt;

    /* Apply configuration */
    if(pObj->IO.WriteReg(pObj->DevAddr, DP83826E_IMR, readval) < 0)
    {
      status = DP83826E_STATUS_WRITE_ERROR;
    }
  }
  else
  {
    status = DP83826E_STATUS_READ_ERROR;
  }

  return status;
}

/**
  * @brief  Clear IT flag.
  * @param  pObj: Pointer to device object.
  * @param  Interrupt: IT flag to be cleared
  *         should be a value or a combination of the following:
  *         DP83826E_WOL_IT
  *         DP83826E_ENERGYON_IT
  *         DP83826E_AUTONEGO_COMPLETE_IT
  *         DP83826E_REMOTE_FAULT_IT
  *         DP83826E_LINK_DOWN_IT
  *         DP83826E_AUTONEGO_LP_ACK_IT
  *         DP83826E_PARALLEL_DETECTION_FAULT_IT
  *         DP83826E_AUTONEGO_PAGE_RECEIVED_IT
  * @retval DP83826E_STATUS_OK  if OK
  *         DP83826E_STATUS_READ_ERROR if connot read register
  */
int32_t  DP83826E_ClearIT(dp83826e_Object_t *pObj, uint32_t Interrupt)
{
  uint32_t readval = 0;
  int32_t status = DP83826E_STATUS_OK;

  if(pObj->IO.ReadReg(pObj->DevAddr, DP83826E_ISFR, &readval) < 0)
  {
    status =  DP83826E_STATUS_READ_ERROR;
  }

  return status;
}

/**
  * @brief  Get IT Flag status.
  * @param  pObj: Pointer to device object.
  * @param  Interrupt: IT Flag to be checked,
  *         should be a value or a combination of the following:
  *         DP83826E_WOL_IT
  *         DP83826E_ENERGYON_IT
  *         DP83826E_AUTONEGO_COMPLETE_IT
  *         DP83826E_REMOTE_FAULT_IT
  *         DP83826E_LINK_DOWN_IT
  *         DP83826E_AUTONEGO_LP_ACK_IT
  *         DP83826E_PARALLEL_DETECTION_FAULT_IT
  *         DP83826E_AUTONEGO_PAGE_RECEIVED_IT
  * @retval 1 IT flag is SET
  *         0 IT flag is RESET
  *         DP83826E_STATUS_READ_ERROR if connot read register
  */
int32_t DP83826E_GetITStatus(dp83826e_Object_t *pObj, uint32_t Interrupt)
{
  uint32_t readval = 0;
  int32_t status = 0;

  if(pObj->IO.ReadReg(pObj->DevAddr, DP83826E_ISFR, &readval) >= 0)
  {
    status = ((readval & Interrupt) == Interrupt);
  }
  else
  {
    status = DP83826E_STATUS_READ_ERROR;
  }

  return status;
}

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
