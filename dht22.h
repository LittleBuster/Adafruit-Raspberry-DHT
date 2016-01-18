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


struct dht22 {
    uint8_t pin;
    uint8_t data[5];
};


/**
 * DHT22 library initialization
 * @dht: dht22 structure
 * @pin: dht22 gpio number
 *
 * returns 0 if succeful
 * returns -1 if fail init
 */
int dht22_init(struct dht22 *dht, uint8_t pin);

/**
 * @dht: dht22 structure
 * @temp: temperature pointer
 * @hum: humidity pointer
 */
int dht22_read_data(struct dht22 *dht, float *temp, float *hum);


#endif
