/*
 * Copyright (c) 2023 Thomas Sutton <me@thomas-sutton.id.au>
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#include <bpfilter.h>

#include <sys/param.h>
#include <sys/systm.h>
#include <sys/sockio.h>
#include <sys/mbuf.h>
#include <sys/kernel.h>
#include <sys/socket.h>
#include <sys/device.h>

#include <net/if.h>

#if NBPFILTER > 0
#include <net/bpf.h>
#endif

#include <netinet/in.h>
#include <netinet/if_ether.h>

#include <dev/usb/usb.h>
#include <dev/usb/usbdi.h>
#include <dev/usb/usbdi_util.h>
#include <dev/usb/usbdevs.h>
#include <dev/usb/usbcdc.h>

#include <dev/usb/if_uncmreg.h>

int uncm_match(struct device *, void *, void *);
void uncm_attach(struct device *, struct device *, void *);
int uncm_detach(struct device *, int);

struct cfdriver uncm_cd = {
	NULL, "uncm", DV_IFNET
};

const struct cfattach uncm_ca = {
	sizeof(struct uncm_softc), uncm_match, uncm_attach, uncm_detach
};

int
uncm_match(struct device *parent, void *match, void *aux) {
        struct usb_attach_arg *uaa = aux;
        usb_interface_descriptor_t *id;

        if (uaa->iface == NULL)
		return (UMATCH_NONE);

        id = usbd_get_interface_descriptor(uaa->iface);
	if (id == NULL)
		return (UMATCH_NONE);

	if (id->bInterfaceClass == UICLASS_CDC &&
	    id->bInterfaceSubClass == UISUBCLASS_NETWORK_CONTROL_MODEL)
            return (UMATCH_IFACECLASS_IFACESUBCLASS);

        return (UMATCH_NONE);
}

void
uncm_attach(struct device *parent, struct device *self, void *aux) {
        struct uncm_softc		*sc = (struct uncm_softc *)self;
        struct usb_attach_arg		*uaa = aux;
        int				 s;
        struct ifnet			*ifp = GET_IFP(sc);
        struct usbd_device		*dev = uaa->device;

        usb_interface_descriptor_t	*id;
	usb_endpoint_descriptor_t	*ed;
        struct usb_cdc_union_descriptor	*ud;

}

int
uncm_detach(struct device *self, int flags) {
        return (0);
}
