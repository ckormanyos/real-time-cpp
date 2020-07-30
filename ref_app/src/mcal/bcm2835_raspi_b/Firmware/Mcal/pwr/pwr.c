/**
 * @file pwr.c
 *
 * This driver provides the ability to power on and power off hardware, such as
 * the USB Controller, on the BCM2835 SoC used on the Raspberry Pi.  This makes
 * use of the BCM2835's mailbox mechanism.
 */
#include <pwr.h>

static volatile uint32 *const mailbox_regs = (volatile uint32*)MAILBOX_REGS_BASE;

/* BCM2835 mailbox register indices  */
#define MAILBOX_READ               0
#define MAILBOX_STATUS             6
#define MAILBOX_WRITE              8

/* BCM2835 mailbox status flags  */
#define MAILBOX_FULL               0x80000000
#define MAILBOX_EMPTY              0x40000000

/* BCM2835 mailbox channels  */
#define MAILBOX_CHANNEL_POWER_MGMT 0U

/* The BCM2835 mailboxes are used for passing 28-bit messages.  The low 4 bits
 * of the 32-bit value are used to specify the channel over which the message is
 * being transferred  */
#define MAILBOX_CHANNEL_MASK       0xfU

/* Write to the specified channel of the mailbox.  */
static void
bcm2835_mailbox_write(uint32 channel, uint32 value)
{
    while (mailbox_regs[MAILBOX_STATUS] & MAILBOX_FULL)
    {
    }
    mailbox_regs[MAILBOX_WRITE] = (value & ~MAILBOX_CHANNEL_MASK) | channel;
}

/* Read from the specified channel of the mailbox.  */
static uint32
bcm2835_mailbox_read(uint32 channel)
{
    uint32 value;

    while (mailbox_regs[MAILBOX_STATUS] & MAILBOX_EMPTY)
    {
    }
    do
    {
        value = mailbox_regs[MAILBOX_READ];
    } while ((value & MAILBOX_CHANNEL_MASK) != channel);
    return (value & ~MAILBOX_CHANNEL_MASK);
}

/* Retrieve the bitmask of power on/off state.  */
static uint32
bcm2835_get_power_mask(void)
{
    return (bcm2835_mailbox_read(MAILBOX_CHANNEL_POWER_MGMT) >> 4);
}

/* Set the bitmask of power on/off state.  */
static void
bcm2835_set_power_mask(uint32 mask)
{
    bcm2835_mailbox_write(MAILBOX_CHANNEL_POWER_MGMT, mask << 4);
}

/* Bitmask that gives the current on/off state of the BCM2835 hardware.
 * This is a cached value.  */
static uint32 bcm2835_power_mask;

/**
 * Powers on or powers off BCM2835 hardware.
 *
 * @param feature
 *      Device or hardware to power on or off.
 * @param on
 *      ::TRUE to power on; ::FALSE to power off.
 *
 * @return
 *      ::OK if successful; ::SYSERR otherwise.
 */
int bcm2835_setpower(enum board_power_feature feature, boolean on)
{
    uint32 bit;
    uint32 newmask;
    boolean is_on;

    bit = (uint32)(1UL << feature);
    is_on = (bcm2835_power_mask & bit) != 0;
    if (on != is_on)
    {
        newmask = bcm2835_power_mask ^ bit;
        bcm2835_set_power_mask(newmask);
        bcm2835_power_mask = bcm2835_get_power_mask();
        if (bcm2835_power_mask != newmask)
        {
            return 0;
        }
    }
    return 1;
}
