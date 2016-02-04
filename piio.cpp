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

#include <errno.h>
#include <sched.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <string>
#include "piio.h"

using namespace std;


#define BASE 0x20000000
#define GPIO_BASE (BASE + 0x200000)
#define GPIO_LENGTH 4096


void GPIO::init(void)
{
    int fd;

    if (this->m_gpio != NULL)
        return;

    fd = open("/dev/mem", O_RDWR | O_SYNC);
    if (fd == -1)
        throw string("Error open /dev/mem");

    this->m_gpio = (uint32_t *)mmap(NULL, GPIO_LENGTH, PROT_READ | PROT_WRITE, MAP_SHARED, fd, GPIO_BASE);
    close(fd);
    if (this->m_gpio == MAP_FAILED) {
        this->m_gpio = NULL;
        throw string("Error init mmap");
    }
}

void GPIO::setInput(const int gpio)
{
    *(this->m_gpio + ((gpio) / 10)) &= ~(7 << (((gpio) % 10) * 3));
}

void GPIO::setOutput(const int gpio)
{
    setInput(gpio);
    *(this->m_gpio + ((gpio) / 10)) |=  (1 << (((gpio) % 10) * 3));
}

void GPIO::setHigh(const int gpio)
{
    *(this->m_gpio + 7) = 1 << gpio;
}

void GPIO::setLow(const int gpio)
{
    *(this->m_gpio + 10) = 1 << gpio;
}

uint32_t GPIO::read(const int gpio)
{
    return *(this->m_gpio + 13) & (1 << gpio);
}

void GPIO::waitMillis(uint32_t millis)
{
    struct timeval deltatime;
    struct timeval walltime;
    struct timeval endtime;

    deltatime.tv_sec = millis / 1000;
    deltatime.tv_usec = (millis % 1000) * 1000;
    /* Get current time and add delay to find end time. */
    gettimeofday(&walltime, NULL);
    timeradd(&walltime, &deltatime, &endtime);
    /* Tight loop to waste time (and CPU) until enough time as elapsed. */
    while (timercmp(&walltime, &endtime, <))
        gettimeofday(&walltime, NULL);
}

void GPIO::sleepMillis(uint32_t millis)
{
    struct timespec sleep;

    sleep.tv_sec = millis / 1000;
    sleep.tv_nsec = (millis % 1000) * 1000000L;
    while (clock_nanosleep(CLOCK_MONOTONIC, 0, &sleep, &sleep) && errno == EINTR);
}

void GPIO::maxPriority(void)
{
    struct sched_param sched;

    memset(&sched, 0, sizeof(sched));
    /* Use FIFO scheduler with highest priority for the lowest chance of the
     * kernel context switching
     */
    sched.sched_priority = sched_get_priority_max(SCHED_FIFO);
    sched_setscheduler(0, SCHED_FIFO, &sched);
}

void GPIO::defaultPriority(void)
{
    struct sched_param sched;

    memset(&sched, 0, sizeof(sched));
    /* Go back to default scheduler with default 0 priority. */
    sched.sched_priority = 0;
    sched_setscheduler(0, SCHED_OTHER, &sched);
}
