#ifndef __INQUIRYABLEPLAYER_H_
#define __INQUIRYABLEPLAYER_H_

#include "playerinquiry.h"

class InquiryablePlayer{
    public:
    virtual const PlayerInquiry inquiry() = 0;
    virtual ~InquiryablePlayer();
};


#endif // __INQUIRYABLEPLAYER_H_
