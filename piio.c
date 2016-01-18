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

#include "piio.h"


#define BASE 0x20000000
#define GPIO_BASE (BASE + 0x200000)
#define GPIO_LENGTH 4096


static struct {
    volatile uint32_t *gpio;
} io = {
    .gpio = NULL,
};


int pi_init(void)
{
    int fd;

    if (io.gpio != NULL)
        return 0;

    fd = open("/dev/mem", O_RDWR | O_SYNC);
    if (fd == -1)
        return ERR_DEVMEM;

    io.gpio = (uint32_t *)mmap(NULL, GPIO_LENGTH, PROT_READ | PROT_WRITE, MAP_SHARED, fd, GPIO_BASE);
    close(fd);
    if (io.gpio == MAP_FAILED) {
        io.gpio = NULL;
        return ERR_MMAP;
    }
    return 0;
}

void pi_set_input(const int gpio)
{
    *(io.gpio + ((gpio) / 10)) &= ~(7 << (((gpio) % 10) * 3));
}

void pi_set_output(const int gpio)
{
    pi_set_input(gpio);
    *(io.gpio + ((gpio) / 10)) |=  (1 << (((gpio) % 10) * 3));
}

void pi_set_high(const int gpio)
{
    *(io.gpio + 7) = 1 << gpio;
}

void pi_set_low(const int gpio)
{
    *(io.gpio + 10) = 1 << gpio;
}

uint32_t pi_read(const int gpio)
{
    return *(io.gpio + 13) & (1 << gpio);
}

void pi_wait_millis(uint32_t millis)
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

void pi_sleep_millis(uint32_t millis)
{
    struct timespec sleep;

    sleep.tv_sec = millis / 1000;
    sleep.tv_nsec = (millis % 1000) * 1000000L;
    while (clock_nanosleep(CLOCK_MONOTONIC, 0, &sleep, &sleep) && errno == EINTR);
}

void set_max_priority(void)
{
    struct sched_param sched;

    memset(&sched, 0, sizeof(sched));
    /* Use FIFO scheduler with highest priority for the lowest chance of the
       kernel context switching.*/
    sched.sched_priority = sched_get_priority_max(SCHED_FIFO);
    sched_setscheduler(0, SCHED_FIFO, &sched);
}

void set_default_priority(void)
{
    struct sched_param sched;

    memset(&sched, 0, sizeof(sched));
    /* Go back to default scheduler with default 0 priority. */
    sched.sched_priority = 0;
    sched_setscheduler(0, SCHED_OTHER, &sched);
}
