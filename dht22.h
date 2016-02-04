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

#ifndef __DHT22_H__
#define __DHT22_H__

#include <stdint.h>
#include <memory>

using namespace std;


class IGPIO;


class IDHT22
{
public:
    virtual void init(uint8_t pin) = 0;
    virtual void readData(float &temp, float &hum) = 0;
};


class DHT22: public IDHT22
{
private:
    uint8_t pin;
    uint8_t data[5];
    shared_ptr<IGPIO> m_gpio;

public:
    DHT22();

    /**
     * DHT22 library initialization
     * @pin: dht22 gpio number
     *
     * returns 0 if succeful
     * returns -1 if fail init
     */
    void init(uint8_t pin);

    /**
     * Reading temperature and humidity
     * @temp: temperature pointer
     * @hum: humidity pointer
     */
    void readData(float &temp, float &hum);
};


#endif
