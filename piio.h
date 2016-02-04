/* DHT22 Raspberry Pi library
 *
 * Copyright (c) 2014 Adafruit Industries
 * Author: Tony DiCola
 * Rewrited by: Sergey Denisov aka LittleBuster (c) 2016
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef __PI_IO_H__
#define __PI_IO_H__

#include <stdint.h>

enum io_errs {
    ERR_DEVMEM,
    ERR_MMAP
};


class IGPIO
{
public:
    virtual void init(void) = 0;
    virtual void setInput(const int gpio) = 0;
    virtual void setOutput(const int gpio) = 0;
    virtual void setHigh(const int gpio) = 0;
    virtual void setLow(const int gpio) = 0;
    virtual uint32_t read(const int gpio) = 0;
    virtual void waitMillis(uint32_t millis) = 0;
    virtual void sleepMillis(uint32_t millis) = 0;
    virtual void maxPriority(void) = 0;
    virtual void defaultPriority(void) = 0;
};


class GPIO: public IGPIO
{
private:
    volatile uint32_t *m_gpio;

public:
    /**
     * IO library initialization
     *
     * returns 0 if succeful
     * returns ERR_DEVMEM if fail init (need root)
     * returns ERR_MMAP if fail reading mmap
     */
    void init(void);

    /**
     * Set port in input mode
     * @gpio: port number
     */
    void setInput(const int gpio);

    /**
     * Set port in input mode
     * @gpio: port number
     */
    void setOutput(const int gpio);

    /**
     * Set port in high level
     * @gpio: port number
     */
    void setHigh(const int gpio);

    /**
     * Set port in low level
     * @gpio: port number
     */
    void setLow(const int gpio);

    /**
     * Reading data from port
     * @gpio: port number
     *
     * returns port value
     */
    uint32_t read(const int gpio);

    /**
     * Busy wait delay for most accurate timing, but high CPU usage.
     * Only use this for short periods of time (a few hundred milliseconds at most)!
     * @millis: wait milliseconds
     */
    void waitMillis(uint32_t millis);

    /**
     * General delay that sleeps so CPU usage is low,
     * but accuracy is potentially bad.
     * @millis: sleep milliseconds
     */
    void sleepMillis(uint32_t millis);

    /*
     * Increase scheduling priority and algorithm to try to get 'real time' results.
     */
    void maxPriority(void);

    /*
     * Drop scheduling priority back to normal/default.
     */
    void defaultPriority(void);
};


#endif
