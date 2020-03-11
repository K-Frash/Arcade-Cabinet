#ifndef __INQUIRYABLECARD_H_
#define __INQUIRYABLECARD_H_

#include "inquiryablecard.h"
#include "cardinquiry.h"

struct CardBase;

class InquiryableCard{
    public:
    virtual const CardInquiry inquiry() const = 0;
    virtual const CardInquiry inquiryBase() const;
    virtual ~InquiryableCard();
};

#endif // __INQUIRYABLECARD_H_
