/*
 *****************************************************************************
 * Copyright by ams AG                                                       *
 * All rights are reserved.                                                  *
 *                                                                           *
 * IMPORTANT - PLEASE READ CAREFULLY BEFORE COPYING, INSTALLING OR USING     *
 * THE SOFTWARE.                                                             *
 *                                                                           *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS       *
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT         *
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS         *
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT  *
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,     *
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT          *
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,     *
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY     *
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT       *
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE     *
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.      *
 *****************************************************************************
 */
/*
 *      PROJECT:   AS1130 MCU board firmware
 *      $Revision: $
 *      LANGUAGE:  ANSI C
 */

/*! \file
 *
 *  \author Wolfgang Reichart, 
 *          Bernhard Breinbauer 
 *
 *  \brief uart driver declaration file
 *
 */
/*!
 *
 * The UART driver provides basic functionalty for sending and receiving
 * data via serial interface. \n
 * The code for receiving data is only enabled if USE_UART_RECEIVE
 * or USE_UART_STREAM_DRIVER is defined.\n
 * At the moment only UART1 is supported.
 *
 * API:
 * - Initialize UART driver: #uartTxInitialize()/uartRxInitialize()/uartInitialize()
 * - Deinitialize UART driver: #uartTxDeinitialize
 * - Transmit data: #uartTxNBytes
 * - size of received data: #uartRxNumBytesAvailable
 * - get received data: #uartRxNBytes
 */

//#ifndef UART_DRIVER_H__
#define UART_DRIVER_H__

/*
******************************************************************************
* INCLUDES
******************************************************************************
*/
#include "ams_types.h"

/*
******************************************************************************
* LOCAL MACROS
******************************************************************************
*/
#ifdef USE_UART_RECEIVE
#define UART_RECEIVE_ENABLED
#endif
//#ifdef USE_UART_STREAM_DRIVER
#define UART_RECEIVE_ENABLED

/*!
 * macro which writes to uart config/status registers depending on selected
 * instance.
 */
#define UART_WRITE_REG(REG, VALUE) U1##REG = (VALUE)
#define UART2_WRITE_REG(REG, VALUE) U2##REG = (VALUE)
#define UART3_WRITE_REG(REG, VALUE) U3##REG = (VALUE)
#define UART4_WRITE_REG(REG, VALUE) U4##REG = (VALUE)


/*!
 * macro which reads from uart config/status registers depending on selected
 * instance.
 */
#define UART_READ_REG(REG) U1##REG
#define UART2_READ_REG(REG) U2##REG
#define UART3_READ_REG(REG) U3##REG
#define UART4_READ_REG(REG) U4##REG


#ifdef UART_RECEIVE_ENABLED
#define UART_RX_BUFFER_SIZE 1024         /* At a baudrate of 115200 it takes ~11ms to fill it.
The driver has to be polled in this time frame. */
//#endif

/*
******************************************************************************
* GLOBAL FUNCTION PROTOTYPES
******************************************************************************
*/
/*!
 *****************************************************************************
 *  \brief  Initialize UART TX interface
 *
 *  This function initializes the UART interface, i.e. sets the requested
 *  baudrate and enables transmission only.
 *  \note System frequency must not be changed since baudrate calculation is
 *  done on base of a fixed frequency.
 *
 *  \param[in] sysclk: clk frequency the system is configured to
 *  \param[in] baudrate: Baudrate to set, e.g. 115200
 *  \param[out] actbaudrate: Actual set baudrate which normally differs from
 *                    requested \a baudrate due to divider error.
 *  \return ERR_NONE : No error, UART initialized.
 *
 *****************************************************************************
 */
extern s8 uartTxInitialize(u32 sysclk, u32 baudrate, u32* actbaudrate);
extern s8 uart2TxInitialize(u32 sysclk, u32 baudrate, u32* actbaudrate);
extern s8 uart3TxInitialize(u32 sysclk, u32 baudrate, u32* actbaudrate);
extern s8 uart4TxInitialize(u32 sysclk, u32 baudrate, u32* actbaudrate);


/*!
 *****************************************************************************
 *  \brief  Initialize UART RX interface
 *
 *  This function initializes the UART RX driver functionality.
 *  To get received data from the driver use uartRxNBytes().
 *  NOTE: the baud rate etc, has to be set with uartTxInitialize()
 *
 *  \return ERR_NONE : No error, UART initialized.
 *
 *****************************************************************************
 */
extern s8 uartRx1Initialize();
extern s8 uartRx2Initialize();
extern s8 uartRx3Initialize();
extern s8 uartRx4Initialize();

/*!
 *****************************************************************************
 *  \brief  Initialize UART interface for Tx and Rx
 *
 *  The function calls uartTxInitialize() and uartRxInitialize() - the
 *  second one only if uart rx functionality is enabled.
 *
 *  \param[in] sysclk: clk frequency the system is configured to
 *  \param[in] baudrate: Baudrate to set, e.g. 115200
 *  \param[out] actbaudrate: Actual set baudrate which normally differs from
 *                    requested \a baudrate due to divider error.
 *  \return ERR_NONE : No error, UART initialized.
 *
 *****************************************************************************
 */
extern s8 uartInitialize(u32 sysclk, u32 baudrate, u32* actbaudrate);

/*!
 *****************************************************************************
 *  \brief  Deinitialize UART TX interface
 *
 *  Calling this function deinitializes the UART interface.
 *  Transmitting is then not possible any more.
 *
 *  \return ERR_NONE : No error, UART deinitialized.
 *
 *****************************************************************************
 */
extern s8 uartTxDeinitialize();

/*!
 *****************************************************************************
 *  \brief  Deinitialize UART interface
 *
 *  Calls uartTxDeinitialize().
 *
 *  \return ERR_NONE : No error, UART deinitialized.
 *
 *****************************************************************************
 */
extern s8 uartDeinitialize();

/*!
 *****************************************************************************
 *  \brief  Transmit a zero-termianted string
 *
 *  This function is used to transmit a zero-terminated string.
 *
 *  \param[in] text: zero-terminated string
 *
 *  \return ERR_NONE : No error, all data sent.
 *
 *****************************************************************************
 */
extern s8 uartTxString(const char * text);

/*!
 *****************************************************************************
 *  \brief  Transmit a given number of bytes
 *
 *  This function is used to transmit \a length bytes via the UART interface.
 *  \note blocking implementation, i.e. Function doesn't return before all
 *  data has been sent.
 *
 *  \param[in] buffer: Buffer of size \a length to be transmitted.
 *  \param[in] length: Number of bytes to be transmitted.
 *
 *  \return ERR_NONE : No error, all data sent.
 *
 *****************************************************************************
 */
extern s8 uartTxNBytes(const u8* buffer, u16 length);


/*!
 *****************************************************************************
 *  \brief  transmit a single byte
 *
 *  This function is used to transmit a single byte
 *
 *  \param[in] dat: byte to be transmitted.
 *
 *  \return ERR_NONE : No error, byte sent.
 *
 *****************************************************************************
 */
extern s8 uartTxByte(u8 dat);

/*!
 *****************************************************************************
 *  \brief  transmit a single byte
 *
 *  This macro is used to transmit a single byte.
 *
 *  \param[in] dat: Byte to transmit.
 *
 *  \return nothing
 *
 *****************************************************************************
 */

/*#define uartTx(dat)                                         \
  do {                                                      \
        UART_WRITE_REG(TXREG, dat);                         \
         Wait until transmit shift register is empty   \
        while (!(UART_READ_REG(STA) & 0x100)) ;             \
  } while ( 0 )*/


#ifdef UART_RECEIVE_ENABLED
/*!
 *****************************************************************************
 *  \brief  Get number of received bytes.
 *
 *  Get number of received bytes, which are available in internal buffer.
 *  Currently max size is UART_RX_BUFFER_SIZE.
 *
 *  \return number of bytes.
 *
 *****************************************************************************
 */
extern u16 uartRxNumBytesAvailable();
extern u16 uartRx3NumBytesAvailable();
extern u16 uartRx4NumBytesAvailable();

/*!
 *****************************************************************************
 *  \brief  Get received bytes.
 *
 *  Get bytes which have been received from the UART rx. The data will be
 *  copied from the internal buffer to the buffer. numBytes will be set to
 *  the number of bytes which have been copied to buffer.
 *
 *  \param buffer Buffer where received data will be copied to.
 *  \param [in]numBytes:  number of bytes that can be hold in the buffer
 *         [out]numBytes: number of bytes that have been copied into buffer
 *
 *  \return error codes as defined in errno.h
 *
 *****************************************************************************
 */
extern s8 uartRxNBytes( u8 * buffer, u16 * numBytes);
extern s8 uartRx2NBytes( u8 * buffer, u16 * numBytes);
extern s8 uartRx3NBytes( u8 * buffer, u16 * numBytes);

void uart1Tx (u8 dado);
void uart2Tx (u8 dado);
void uart3Tx (u8 dado);
void uart4Tx (u8 dado);
#endif /* UART_RECEIVE_ENABLED */

#endif /* UART_DRIVER_H__ */

