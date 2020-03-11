#include "inquiryablecard.h"

InquiryableCard::~InquiryableCard(){}

const CardInquiry InquiryableCard::inquiryBase() const{
    return this->inquiry();
};
