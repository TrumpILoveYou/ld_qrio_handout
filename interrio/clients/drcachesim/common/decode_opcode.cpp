#include "decode_opcode.h"
#include "opcode.h"

int decode_opcode(unsigned int enc)
{
    if ((enc >> 26 & 1) == 0) {
        if ((enc >> 22 & 1) == 0) {
            if ((enc >> 30 & 1) == 0) {
                if ((enc >> 23 & 1) == 0) {
                    if ((enc >> 31 & 1) == 0) {
                        if ((enc >> 25 & 1) == 0) {
                            if ((enc >> 21 & 1) == 0) {
                                if ((enc >> 24 & 1) == 0) {
                                    if ((enc >> 28 & 1) == 0) {
                                        if ((enc & 0xffe08000) == 0x08008000)
                                            return OP_stlxrb;
                                        if ((enc & 0xffc00000) == 0x28000000)
                                            return OP_stnp;
                                        if ((enc & 0xffe08000) == 0x08000000)
                                            return OP_stxrb;
                                    } else {
                                        if ((enc >> 10 & 1) == 0) {
                                            if ((enc >> 11 & 1) == 0) {
                                                if ((enc & 0x9f000000) == 0x10000000)
                                                    return OP_adr;
                                                if ((enc & 0xff000000) == 0x18000000)
                                                    return OP_ldr;
                                                if ((enc & 0xffe00c00) == 0x38000000)
                                                    return OP_sturb;
                                            } else {
                                                if ((enc & 0x9f000000) == 0x10000000)
                                                    return OP_adr;
                                                if ((enc & 0xff000000) == 0x18000000)
                                                    return OP_ldr;
                                                if ((enc & 0xffe00c00) == 0x38000800)
                                                    return OP_sttrb;
                                            }
                                        } else {
                                            if ((enc >> 11 & 1) == 0) {
                                                if ((enc & 0x9f000000) == 0x10000000)
                                                    return OP_adr;
                                                if ((enc & 0xff000000) == 0x18000000)
                                                    return OP_ldr;
                                                if ((enc & 0xffe00c00) == 0x38000400)
                                                    return OP_strb;
                                            } else {
                                                if ((enc & 0x9f000000) == 0x10000000)
                                                    return OP_adr;
                                                if ((enc & 0xff000000) == 0x18000000)
                                                    return OP_ldr;
                                                if ((enc & 0xffe00c00) == 0x38000c00)
                                                    return OP_strb;
                                            }
                                        }
                                    }
                                } else {
                                    if ((enc >> 27 & 1) == 0) {
                                        if ((enc & 0x7f800000) == 0x11000000)
                                            return OP_add;
                                        if ((enc & 0x7f800000) == 0x31000000)
                                            return OP_adds;
                                    } else {
                                        if ((enc & 0xffc00000) == 0x29000000)
                                            return OP_stp;
                                        if ((enc & 0xffc00000) == 0x39000000)
                                            return OP_strb;
                                    }
                                }
                            } else {
                                if ((enc >> 12 & 1) == 0) {
                                    if ((enc >> 24 & 1) == 0) {
                                        if ((enc >> 13 & 1) == 0) {
                                            if ((enc >> 11 & 1) == 0) {
                                                if ((enc >> 14 & 1) == 0) {
                                                    if ((enc >> 15 & 1) == 0) {
                                                        if ((enc >> 27 & 1) == 0) {
                                                            if ((enc & 0x9f000000) == 0x10000000)
                                                                return OP_adr;
                                                        } else {
                                                            if ((enc & 0xffe0fc00) == 0x38200000)
                                                                return OP_ldaddb;
                                                            if ((enc & 0xff000000) == 0x18000000)
                                                                return OP_ldr;
                                                            if ((enc & 0xffc00000) == 0x28000000)
                                                                return OP_stnp;
                                                        }
                                                    } else {
                                                        if ((enc >> 27 & 1) == 0) {
                                                            if ((enc & 0x9f000000) == 0x10000000)
                                                                return OP_adr;
                                                        } else {
                                                            if ((enc & 0xff000000) == 0x18000000)
                                                                return OP_ldr;
                                                            if ((enc & 0xffc00000) == 0x28000000)
                                                                return OP_stnp;
                                                            if ((enc & 0xffe0fc00) == 0x38208000)
                                                                return OP_swpb;
                                                        }
                                                    }
                                                } else {
                                                    if ((enc >> 27 & 1) == 0) {
                                                        if ((enc & 0x9f000000) == 0x10000000)
                                                            return OP_adr;
                                                    } else {
                                                        if ((enc & 0xff000000) == 0x18000000)
                                                            return OP_ldr;
                                                        if ((enc & 0xffe0fc00) == 0x38204000)
                                                            return OP_ldsmaxb;
                                                        if ((enc & 0xffc00000) == 0x28000000)
                                                            return OP_stnp;
                                                    }
                                                }
                                            } else {
                                                if ((enc >> 27 & 1) == 0) {
                                                    if ((enc & 0x9f000000) == 0x10000000)
                                                        return OP_adr;
                                                } else {
                                                    if ((enc & 0xff000000) == 0x18000000)
                                                        return OP_ldr;
                                                    if ((enc & 0xffc00000) == 0x28000000)
                                                        return OP_stnp;
                                                    if ((enc & 0xffe00c00) == 0x38200800)
                                                        return OP_strb;
                                                }
                                            }
                                        } else {
                                            if ((enc >> 11 & 1) == 0) {
                                                if ((enc >> 14 & 1) == 0) {
                                                    if ((enc >> 27 & 1) == 0) {
                                                        if ((enc & 0x9f000000) == 0x10000000)
                                                            return OP_adr;
                                                    } else {
                                                        if ((enc & 0xffe0fc00) == 0x38202000)
                                                            return OP_ldeorb;
                                                        if ((enc & 0xff000000) == 0x18000000)
                                                            return OP_ldr;
                                                        if ((enc & 0xffc00000) == 0x28000000)
                                                            return OP_stnp;
                                                    }
                                                } else {
                                                    if ((enc >> 27 & 1) == 0) {
                                                        if ((enc & 0x9f000000) == 0x10000000)
                                                            return OP_adr;
                                                    } else {
                                                        if ((enc & 0xff000000) == 0x18000000)
                                                            return OP_ldr;
                                                        if ((enc & 0xffe0fc00) == 0x38206000)
                                                            return OP_ldumaxb;
                                                        if ((enc & 0xffc00000) == 0x28000000)
                                                            return OP_stnp;
                                                    }
                                                }
                                            } else {
                                                if ((enc >> 27 & 1) == 0) {
                                                    if ((enc & 0x9f000000) == 0x10000000)
                                                        return OP_adr;
                                                } else {
                                                    if ((enc & 0xff000000) == 0x18000000)
                                                        return OP_ldr;
                                                    if ((enc & 0xffc00000) == 0x28000000)
                                                        return OP_stnp;
                                                    if ((enc & 0xffe00c00) == 0x38200800)
                                                        return OP_strb;
                                                }
                                            }
                                        }
                                    } else {
                                        if ((enc >> 27 & 1) == 0) {
                                            if ((enc & 0x7f800000) == 0x11000000)
                                                return OP_add;
                                            if ((enc & 0x7f800000) == 0x31000000)
                                                return OP_adds;
                                        } else {
                                            if ((enc & 0xffc00000) == 0x29000000)
                                                return OP_stp;
                                            if ((enc & 0xffc00000) == 0x39000000)
                                                return OP_strb;
                                        }
                                    }
                                } else {
                                    if ((enc >> 24 & 1) == 0) {
                                        if ((enc >> 11 & 1) == 0) {
                                            if ((enc >> 13 & 1) == 0) {
                                                if ((enc >> 14 & 1) == 0) {
                                                    if ((enc >> 27 & 1) == 0) {
                                                        if ((enc & 0x9f000000) == 0x10000000)
                                                            return OP_adr;
                                                    } else {
                                                        if ((enc & 0xffe0fc00) == 0x38201000)
                                                            return OP_ldclrb;
                                                        if ((enc & 0xff000000) == 0x18000000)
                                                            return OP_ldr;
                                                        if ((enc & 0xffc00000) == 0x28000000)
                                                            return OP_stnp;
                                                    }
                                                } else {
                                                    if ((enc >> 27 & 1) == 0) {
                                                        if ((enc & 0x9f000000) == 0x10000000)
                                                            return OP_adr;
                                                    } else {
                                                        if ((enc & 0xff000000) == 0x18000000)
                                                            return OP_ldr;
                                                        if ((enc & 0xffe0fc00) == 0x38205000)
                                                            return OP_ldsminb;
                                                        if ((enc & 0xffc00000) == 0x28000000)
                                                            return OP_stnp;
                                                    }
                                                }
                                            } else {
                                                if ((enc >> 14 & 1) == 0) {
                                                    if ((enc >> 27 & 1) == 0) {
                                                        if ((enc & 0x9f000000) == 0x10000000)
                                                            return OP_adr;
                                                    } else {
                                                        if ((enc & 0xff000000) == 0x18000000)
                                                            return OP_ldr;
                                                        if ((enc & 0xffe0fc00) == 0x38203000)
                                                            return OP_ldsetb;
                                                        if ((enc & 0xffc00000) == 0x28000000)
                                                            return OP_stnp;
                                                    }
                                                } else {
                                                    if ((enc >> 27 & 1) == 0) {
                                                        if ((enc & 0x9f000000) == 0x10000000)
                                                            return OP_adr;
                                                    } else {
                                                        if ((enc & 0xff000000) == 0x18000000)
                                                            return OP_ldr;
                                                        if ((enc & 0xffe0fc00) == 0x38207000)
                                                            return OP_lduminb;
                                                        if ((enc & 0xffc00000) == 0x28000000)
                                                            return OP_stnp;
                                                    }
                                                }
                                            }
                                        } else {
                                            if ((enc >> 28 & 1) == 0) {
                                                if ((enc & 0xffe0fc00) == 0x08207c00)
                                                    return OP_casp;
                                                if ((enc & 0xffe0fc00) == 0x0820fc00)
                                                    return OP_caspl;
                                                if ((enc & 0xffc00000) == 0x28000000)
                                                    return OP_stnp;
                                            } else {
                                                if ((enc & 0x9f000000) == 0x10000000)
                                                    return OP_adr;
                                                if ((enc & 0xff000000) == 0x18000000)
                                                    return OP_ldr;
                                                if ((enc & 0xffe00c00) == 0x38200800)
                                                    return OP_strb;
                                            }
                                        }
                                    } else {
                                        if ((enc >> 27 & 1) == 0) {
                                            if ((enc & 0x7f800000) == 0x11000000)
                                                return OP_add;
                                            if ((enc & 0x7f800000) == 0x31000000)
                                                return OP_adds;
                                        } else {
                                            if ((enc & 0xffc00000) == 0x29000000)
                                                return OP_stp;
                                            if ((enc & 0xffc00000) == 0x39000000)
                                                return OP_strb;
                                        }
                                    }
                                }
                            }
                        } else {
                            if ((enc >> 24 & 1) == 0) {
                                if ((enc >> 28 & 1) == 0) {
                                    if ((enc >> 21 & 1) == 0) {
                                        if ((enc & 0x7f200000) == 0x0a000000)
                                            return OP_and;
                                        if ((enc & 0x7f200000) == 0x2a000000)
                                            return OP_orr;
                                    } else {
                                        if ((enc & 0x7f200000) == 0x0a200000)
                                            return OP_bic;
                                        if ((enc & 0x7f200000) == 0x2a200000)
                                            return OP_orn;
                                    }
                                } else {
                                    if ((enc >> 27 & 1) == 0) {
                                        if ((enc & 0x7f800000) == 0x12000000)
                                            return OP_and;
                                        if ((enc & 0x7f800000) == 0x32000000)
                                            return OP_orr;
                                    } else {
                                        if ((enc & 0x7fe0fc00) == 0x1a000000)
                                            return OP_adc;
                                        if ((enc & 0x7fe0fc00) == 0x3a000000)
                                            return OP_adcs;
                                    }
                                }
                            } else {
                                if ((enc >> 28 & 1) == 0) {
                                    if ((enc >> 21 & 1) == 0) {
                                        if ((enc & 0x7f200000) == 0x0b000000)
                                            return OP_add;
                                        if ((enc & 0x7f200000) == 0x2b000000)
                                            return OP_adds;
                                    } else {
                                        if ((enc & 0x7fe00000) == 0x0b200000)
                                            return OP_add;
                                        if ((enc & 0x7fe00000) == 0x2b200000)
                                            return OP_adds;
                                    }
                                } else {
                                    if ((enc >> 27 & 1) == 0) {
                                        if ((enc & 0xffc00000) == 0x33000000)
                                            return OP_bfm;
                                        if ((enc & 0xffc00000) == 0x13000000)
                                            return OP_sbfm;
                                    } else {
                                        if ((enc & 0x7fe08000) == 0x1b000000)
                                            return OP_madd;
                                        if ((enc & 0x7fe08000) == 0x1b008000)
                                            return OP_msub;
                                    }
                                }
                            }
                        }
                    } else {
                        if ((enc >> 25 & 1) == 0) {
                            if ((enc >> 21 & 1) == 0) {
                                if ((enc >> 24 & 1) == 0) {
                                    if ((enc >> 28 & 1) == 0) {
                                        if ((enc & 0xffe08000) == 0x88008000)
                                            return OP_stlxr;
                                        if ((enc & 0xffc00000) == 0xa8000000)
                                            return OP_stnp;
                                        if ((enc & 0xffe08000) == 0x88000000)
                                            return OP_stxr;
                                    } else {
                                        if ((enc >> 10 & 1) == 0) {
                                            if ((enc >> 11 & 1) == 0) {
                                                if ((enc & 0x9f000000) == 0x90000000)
                                                    return OP_adrp;
                                                if ((enc & 0xff000000) == 0x98000000)
                                                    return OP_ldrsw;
                                                if ((enc & 0xffe00c00) == 0xb8000000)
                                                    return OP_stur;
                                            } else {
                                                if ((enc & 0x9f000000) == 0x90000000)
                                                    return OP_adrp;
                                                if ((enc & 0xff000000) == 0x98000000)
                                                    return OP_ldrsw;
                                                if ((enc & 0xffe00c00) == 0xb8000800)
                                                    return OP_sttr;
                                            }
                                        } else {
                                            if ((enc >> 11 & 1) == 0) {
                                                if ((enc & 0x9f000000) == 0x90000000)
                                                    return OP_adrp;
                                                if ((enc & 0xff000000) == 0x98000000)
                                                    return OP_ldrsw;
                                                if ((enc & 0xffe00c00) == 0xb8000400)
                                                    return OP_str;
                                            } else {
                                                if ((enc & 0x9f000000) == 0x90000000)
                                                    return OP_adrp;
                                                if ((enc & 0xff000000) == 0x98000000)
                                                    return OP_ldrsw;
                                                if ((enc & 0xffe00c00) == 0xb8000c00)
                                                    return OP_str;
                                            }
                                        }
                                    }
                                } else {
                                    if ((enc >> 27 & 1) == 0) {
                                        if ((enc & 0x7f800000) == 0x11000000)
                                            return OP_add;
                                        if ((enc & 0x7f800000) == 0x31000000)
                                            return OP_adds;
                                    } else {
                                        if ((enc & 0xffc00000) == 0xa9000000)
                                            return OP_stp;
                                        if ((enc & 0xffc00000) == 0xb9000000)
                                            return OP_str;
                                    }
                                }
                            } else {
                                if ((enc >> 12 & 1) == 0) {
                                    if ((enc >> 24 & 1) == 0) {
                                        if ((enc >> 28 & 1) == 0) {
                                            if ((enc & 0xffe08000) == 0x88208000)
                                                return OP_stlxp;
                                            if ((enc & 0xffc00000) == 0xa8000000)
                                                return OP_stnp;
                                            if ((enc & 0xffe08000) == 0x88200000)
                                                return OP_stxp;
                                        } else {
                                            if ((enc >> 13 & 1) == 0) {
                                                if ((enc >> 11 & 1) == 0) {
                                                    if ((enc >> 14 & 1) == 0) {
                                                        if ((enc >> 15 & 1) == 0) {
                                                            if ((enc & 0x9f000000) == 0x90000000)
                                                                return OP_adrp;
                                                            if ((enc & 0xffe0fc00) == 0xb8200000)
                                                                return OP_ldadd;
                                                            if ((enc & 0xff000000) == 0x98000000)
                                                                return OP_ldrsw;
                                                        } else {
                                                            if ((enc & 0x9f000000) == 0x90000000)
                                                                return OP_adrp;
                                                            if ((enc & 0xff000000) == 0x98000000)
                                                                return OP_ldrsw;
                                                            if ((enc & 0xffe0fc00) == 0xb8208000)
                                                                return OP_swp;
                                                        }
                                                    } else {
                                                        if ((enc & 0x9f000000) == 0x90000000)
                                                            return OP_adrp;
                                                        if ((enc & 0xff000000) == 0x98000000)
                                                            return OP_ldrsw;
                                                        if ((enc & 0xffe0fc00) == 0xb8204000)
                                                            return OP_ldsmax;
                                                    }
                                                } else {
                                                    if ((enc & 0x9f000000) == 0x90000000)
                                                        return OP_adrp;
                                                    if ((enc & 0xff000000) == 0x98000000)
                                                        return OP_ldrsw;
                                                    if ((enc & 0xffe00c00) == 0xb8200800)
                                                        return OP_str;
                                                }
                                            } else {
                                                if ((enc >> 11 & 1) == 0) {
                                                    if ((enc >> 14 & 1) == 0) {
                                                        if ((enc & 0x9f000000) == 0x90000000)
                                                            return OP_adrp;
                                                        if ((enc & 0xffe0fc00) == 0xb8202000)
                                                            return OP_ldeor;
                                                        if ((enc & 0xff000000) == 0x98000000)
                                                            return OP_ldrsw;
                                                    } else {
                                                        if ((enc & 0x9f000000) == 0x90000000)
                                                            return OP_adrp;
                                                        if ((enc & 0xff000000) == 0x98000000)
                                                            return OP_ldrsw;
                                                        if ((enc & 0xffe0fc00) == 0xb8206000)
                                                            return OP_ldumax;
                                                    }
                                                } else {
                                                    if ((enc & 0x9f000000) == 0x90000000)
                                                        return OP_adrp;
                                                    if ((enc & 0xff000000) == 0x98000000)
                                                        return OP_ldrsw;
                                                    if ((enc & 0xffe00c00) == 0xb8200800)
                                                        return OP_str;
                                                }
                                            }
                                        }
                                    } else {
                                        if ((enc >> 27 & 1) == 0) {
                                            if ((enc & 0x7f800000) == 0x11000000)
                                                return OP_add;
                                            if ((enc & 0x7f800000) == 0x31000000)
                                                return OP_adds;
                                        } else {
                                            if ((enc & 0xffc00000) == 0xa9000000)
                                                return OP_stp;
                                            if ((enc & 0xffc00000) == 0xb9000000)
                                                return OP_str;
                                        }
                                    }
                                } else {
                                    if ((enc >> 24 & 1) == 0) {
                                        if ((enc >> 28 & 1) == 0) {
                                            if ((enc & 0xffe08000) == 0x88208000)
                                                return OP_stlxp;
                                            if ((enc & 0xffc00000) == 0xa8000000)
                                                return OP_stnp;
                                            if ((enc & 0xffe08000) == 0x88200000)
                                                return OP_stxp;
                                        } else {
                                            if ((enc >> 13 & 1) == 0) {
                                                if ((enc >> 11 & 1) == 0) {
                                                    if ((enc >> 14 & 1) == 0) {
                                                        if ((enc & 0x9f000000) == 0x90000000)
                                                            return OP_adrp;
                                                        if ((enc & 0xffe0fc00) == 0xb8201000)
                                                            return OP_ldclr;
                                                        if ((enc & 0xff000000) == 0x98000000)
                                                            return OP_ldrsw;
                                                    } else {
                                                        if ((enc & 0x9f000000) == 0x90000000)
                                                            return OP_adrp;
                                                        if ((enc & 0xff000000) == 0x98000000)
                                                            return OP_ldrsw;
                                                        if ((enc & 0xffe0fc00) == 0xb8205000)
                                                            return OP_ldsmin;
                                                    }
                                                } else {
                                                    if ((enc & 0x9f000000) == 0x90000000)
                                                        return OP_adrp;
                                                    if ((enc & 0xff000000) == 0x98000000)
                                                        return OP_ldrsw;
                                                    if ((enc & 0xffe00c00) == 0xb8200800)
                                                        return OP_str;
                                                }
                                            } else {
                                                if ((enc >> 11 & 1) == 0) {
                                                    if ((enc >> 14 & 1) == 0) {
                                                        if ((enc & 0x9f000000) == 0x90000000)
                                                            return OP_adrp;
                                                        if ((enc & 0xff000000) == 0x98000000)
                                                            return OP_ldrsw;
                                                        if ((enc & 0xffe0fc00) == 0xb8203000)
                                                            return OP_ldset;
                                                    } else {
                                                        if ((enc & 0x9f000000) == 0x90000000)
                                                            return OP_adrp;
                                                        if ((enc & 0xff000000) == 0x98000000)
                                                            return OP_ldrsw;
                                                        if ((enc & 0xffe0fc00) == 0xb8207000)
                                                            return OP_ldumin;
                                                    }
                                                } else {
                                                    if ((enc & 0x9f000000) == 0x90000000)
                                                        return OP_adrp;
                                                    if ((enc & 0xff000000) == 0x98000000)
                                                        return OP_ldrsw;
                                                    if ((enc & 0xffe00c00) == 0xb8200800)
                                                        return OP_str;
                                                }
                                            }
                                        }
                                    } else {
                                        if ((enc >> 27 & 1) == 0) {
                                            if ((enc & 0x7f800000) == 0x11000000)
                                                return OP_add;
                                            if ((enc & 0x7f800000) == 0x31000000)
                                                return OP_adds;
                                        } else {
                                            if ((enc & 0xffc00000) == 0xa9000000)
                                                return OP_stp;
                                            if ((enc & 0xffc00000) == 0xb9000000)
                                                return OP_str;
                                        }
                                    }
                                }
                            }
                        } else {
                            if ((enc >> 24 & 1) == 0) {
                                if ((enc >> 28 & 1) == 0) {
                                    if ((enc >> 21 & 1) == 0) {
                                        if ((enc & 0x7f200000) == 0x0a000000)
                                            return OP_and;
                                        if ((enc & 0x7f200000) == 0x2a000000)
                                            return OP_orr;
                                    } else {
                                        if ((enc & 0x7f200000) == 0x0a200000)
                                            return OP_bic;
                                        if ((enc & 0x7f200000) == 0x2a200000)
                                            return OP_orn;
                                    }
                                } else {
                                    if ((enc >> 27 & 1) == 0) {
                                        if ((enc & 0x7f800000) == 0x12000000)
                                            return OP_and;
                                        if ((enc & 0x7f800000) == 0x32000000)
                                            return OP_orr;
                                    } else {
                                        if ((enc & 0x7fe0fc00) == 0x1a000000)
                                            return OP_adc;
                                        if ((enc & 0x7fe0fc00) == 0x3a000000)
                                            return OP_adcs;
                                    }
                                }
                            } else {
                                if ((enc >> 21 & 1) == 0) {
                                    if ((enc >> 28 & 1) == 0) {
                                        if ((enc & 0x7f200000) == 0x0b000000)
                                            return OP_add;
                                        if ((enc & 0x7f200000) == 0x2b000000)
                                            return OP_adds;
                                    } else {
                                        if ((enc & 0x7fe08000) == 0x1b000000)
                                            return OP_madd;
                                        if ((enc & 0x7fe08000) == 0x1b008000)
                                            return OP_msub;
                                    }
                                } else {
                                    if ((enc >> 28 & 1) == 0) {
                                        if ((enc & 0x7fe00000) == 0x0b200000)
                                            return OP_add;
                                        if ((enc & 0x7fe00000) == 0x2b200000)
                                            return OP_adds;
                                    } else {
                                        if ((enc & 0xffe08000) == 0x9b200000)
                                            return OP_smaddl;
                                        if ((enc & 0xffe08000) == 0x9b208000)
                                            return OP_smsubl;
                                    }
                                }
                            }
                        }
                    }
                } else {
                    if ((enc >> 31 & 1) == 0) {
                        if ((enc >> 21 & 1) == 0) {
                            if ((enc >> 25 & 1) == 0) {
                                if ((enc >> 28 & 1) == 0) {
                                    if ((enc & 0xffe08000) == 0x08808000)
                                        return OP_stlrb;
                                    if ((enc & 0xffc00000) == 0x28800000)
                                        return OP_stp;
                                    if ((enc & 0xffc00000) == 0x29800000)
                                        return OP_stp;
                                } else {
                                    if ((enc >> 10 & 1) == 0) {
                                        if ((enc >> 11 & 1) == 0) {
                                            if ((enc >> 24 & 1) == 0) {
                                                if ((enc & 0x9f000000) == 0x10000000)
                                                    return OP_adr;
                                                if ((enc & 0xff000000) == 0x18000000)
                                                    return OP_ldr;
                                                if ((enc & 0xffe00c00) == 0x38800000)
                                                    return OP_ldursb;
                                            } else {
                                                if ((enc & 0xffc00000) == 0x39800000)
                                                    return OP_ldrsb;
                                            }
                                        } else {
                                            if ((enc >> 24 & 1) == 0) {
                                                if ((enc & 0x9f000000) == 0x10000000)
                                                    return OP_adr;
                                                if ((enc & 0xff000000) == 0x18000000)
                                                    return OP_ldr;
                                                if ((enc & 0xffe00c00) == 0x38800800)
                                                    return OP_ldtrsb;
                                            } else {
                                                if ((enc & 0xffc00000) == 0x39800000)
                                                    return OP_ldrsb;
                                            }
                                        }
                                    } else {
                                        if ((enc >> 11 & 1) == 0) {
                                            if ((enc >> 24 & 1) == 0) {
                                                if ((enc & 0x9f000000) == 0x10000000)
                                                    return OP_adr;
                                                if ((enc & 0xff000000) == 0x18000000)
                                                    return OP_ldr;
                                                if ((enc & 0xffe00c00) == 0x38800400)
                                                    return OP_ldrsb;
                                            } else {
                                                if ((enc & 0xffc00000) == 0x39800000)
                                                    return OP_ldrsb;
                                            }
                                        } else {
                                            if ((enc >> 24 & 1) == 0) {
                                                if ((enc & 0x9f000000) == 0x10000000)
                                                    return OP_adr;
                                                if ((enc & 0xff000000) == 0x18000000)
                                                    return OP_ldr;
                                                if ((enc & 0xffe00c00) == 0x38800c00)
                                                    return OP_ldrsb;
                                            } else {
                                                if ((enc & 0xffc00000) == 0x39800000)
                                                    return OP_ldrsb;
                                            }
                                        }
                                    }
                                }
                            } else {
                                if ((enc >> 28 & 1) == 0) {
                                    if ((enc >> 24 & 1) == 0) {
                                        if ((enc & 0x7f200000) == 0x0a000000)
                                            return OP_and;
                                        if ((enc & 0x7f200000) == 0x2a000000)
                                            return OP_orr;
                                    } else {
                                        if ((enc & 0x7f200000) == 0x0b000000)
                                            return OP_add;
                                        if ((enc & 0x7f200000) == 0x2b000000)
                                            return OP_adds;
                                    }
                                } else {
                                    if ((enc >> 27 & 1) == 0) {
                                        if ((enc & 0xffe00000) == 0x13800000)
                                            return OP_extr;
                                        if ((enc & 0xff800000) == 0x12800000)
                                            return OP_movn;
                                    } else {
                                        if ((enc & 0x7fe00c00) == 0x1a800000)
                                            return OP_csel;
                                        if ((enc & 0x7fe00c00) == 0x1a800400)
                                            return OP_csinc;
                                    }
                                }
                            }
                        } else {
                            if ((enc >> 28 & 1) == 0) {
                                if ((enc >> 29 & 1) == 0) {
                                    if ((enc & 0x7f200000) == 0x0a200000)
                                        return OP_bic;
                                    if ((enc & 0xffe0fc00) == 0x08a07c00)
                                        return OP_casb;
                                    if ((enc & 0xffe0fc00) == 0x08a0fc00)
                                        return OP_caslb;
                                } else {
                                    if ((enc & 0x7f200000) == 0x2a200000)
                                        return OP_orn;
                                    if ((enc & 0xffc00000) == 0x28800000)
                                        return OP_stp;
                                    if ((enc & 0xffc00000) == 0x29800000)
                                        return OP_stp;
                                }
                            } else {
                                if ((enc >> 12 & 1) == 0) {
                                    if ((enc >> 13 & 1) == 0) {
                                        if ((enc >> 27 & 1) == 0) {
                                            if ((enc & 0x9f000000) == 0x10000000)
                                                return OP_adr;
                                            if ((enc & 0xff800000) == 0x12800000)
                                                return OP_movn;
                                        } else {
                                            if ((enc >> 11 & 1) == 0) {
                                                if ((enc >> 14 & 1) == 0) {
                                                    if ((enc >> 15 & 1) == 0) {
                                                        if ((enc & 0xffe0fc00) == 0x38a00000)
                                                            return OP_ldaddab;
                                                        if ((enc & 0xff000000) == 0x18000000)
                                                            return OP_ldr;
                                                        if ((enc & 0xffc00000) == 0x39800000)
                                                            return OP_ldrsb;
                                                    } else {
                                                        if ((enc & 0xff000000) == 0x18000000)
                                                            return OP_ldr;
                                                        if ((enc & 0xffc00000) == 0x39800000)
                                                            return OP_ldrsb;
                                                        if ((enc & 0xffe0fc00) == 0x38a08000)
                                                            return OP_swpab;
                                                    }
                                                } else {
                                                    if ((enc & 0xff000000) == 0x18000000)
                                                        return OP_ldr;
                                                    if ((enc & 0xffc00000) == 0x39800000)
                                                        return OP_ldrsb;
                                                    if ((enc & 0xffe0fc00) == 0x38a04000)
                                                        return OP_ldsmaxab;
                                                }
                                            } else {
                                                if ((enc & 0xff000000) == 0x18000000)
                                                    return OP_ldr;
                                                if ((enc & 0xffe00c00) == 0x38a00800)
                                                    return OP_ldrsb;
                                                if ((enc & 0xffc00000) == 0x39800000)
                                                    return OP_ldrsb;
                                            }
                                        }
                                    } else {
                                        if ((enc >> 27 & 1) == 0) {
                                            if ((enc & 0x9f000000) == 0x10000000)
                                                return OP_adr;
                                            if ((enc & 0xff800000) == 0x12800000)
                                                return OP_movn;
                                        } else {
                                            if ((enc >> 11 & 1) == 0) {
                                                if ((enc >> 14 & 1) == 0) {
                                                    if ((enc & 0xffe0fc00) == 0x38a02000)
                                                        return OP_ldeorab;
                                                    if ((enc & 0xff000000) == 0x18000000)
                                                        return OP_ldr;
                                                    if ((enc & 0xffc00000) == 0x39800000)
                                                        return OP_ldrsb;
                                                } else {
                                                    if ((enc & 0xff000000) == 0x18000000)
                                                        return OP_ldr;
                                                    if ((enc & 0xffc00000) == 0x39800000)
                                                        return OP_ldrsb;
                                                    if ((enc & 0xffe0fc00) == 0x38a06000)
                                                        return OP_ldumaxab;
                                                }
                                            } else {
                                                if ((enc & 0xff000000) == 0x18000000)
                                                    return OP_ldr;
                                                if ((enc & 0xffe00c00) == 0x38a00800)
                                                    return OP_ldrsb;
                                                if ((enc & 0xffc00000) == 0x39800000)
                                                    return OP_ldrsb;
                                            }
                                        }
                                    }
                                } else {
                                    if ((enc >> 13 & 1) == 0) {
                                        if ((enc >> 27 & 1) == 0) {
                                            if ((enc & 0x9f000000) == 0x10000000)
                                                return OP_adr;
                                            if ((enc & 0xff800000) == 0x12800000)
                                                return OP_movn;
                                        } else {
                                            if ((enc >> 11 & 1) == 0) {
                                                if ((enc >> 14 & 1) == 0) {
                                                    if ((enc & 0xffe0fc00) == 0x38a01000)
                                                        return OP_ldclrab;
                                                    if ((enc & 0xff000000) == 0x18000000)
                                                        return OP_ldr;
                                                    if ((enc & 0xffc00000) == 0x39800000)
                                                        return OP_ldrsb;
                                                } else {
                                                    if ((enc & 0xff000000) == 0x18000000)
                                                        return OP_ldr;
                                                    if ((enc & 0xffc00000) == 0x39800000)
                                                        return OP_ldrsb;
                                                    if ((enc & 0xffe0fc00) == 0x38a05000)
                                                        return OP_ldsminab;
                                                }
                                            } else {
                                                if ((enc & 0xff000000) == 0x18000000)
                                                    return OP_ldr;
                                                if ((enc & 0xffe00c00) == 0x38a00800)
                                                    return OP_ldrsb;
                                                if ((enc & 0xffc00000) == 0x39800000)
                                                    return OP_ldrsb;
                                            }
                                        }
                                    } else {
                                        if ((enc >> 27 & 1) == 0) {
                                            if ((enc & 0x9f000000) == 0x10000000)
                                                return OP_adr;
                                            if ((enc & 0xff800000) == 0x12800000)
                                                return OP_movn;
                                        } else {
                                            if ((enc >> 11 & 1) == 0) {
                                                if ((enc >> 14 & 1) == 0) {
                                                    if ((enc & 0xff000000) == 0x18000000)
                                                        return OP_ldr;
                                                    if ((enc & 0xffc00000) == 0x39800000)
                                                        return OP_ldrsb;
                                                    if ((enc & 0xffe0fc00) == 0x38a03000)
                                                        return OP_ldsetab;
                                                } else {
                                                    if ((enc & 0xff000000) == 0x18000000)
                                                        return OP_ldr;
                                                    if ((enc & 0xffc00000) == 0x39800000)
                                                        return OP_ldrsb;
                                                    if ((enc & 0xffe0fc00) == 0x38a07000)
                                                        return OP_lduminab;
                                                }
                                            } else {
                                                if ((enc & 0xff000000) == 0x18000000)
                                                    return OP_ldr;
                                                if ((enc & 0xffe00c00) == 0x38a00800)
                                                    return OP_ldrsb;
                                                if ((enc & 0xffc00000) == 0x39800000)
                                                    return OP_ldrsb;
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    } else {
                        if ((enc >> 29 & 1) == 0) {
                            if ((enc >> 28 & 1) == 0) {
                                if ((enc >> 21 & 1) == 0) {
                                    if ((enc & 0x7f200000) == 0x0b000000)
                                        return OP_add;
                                    if ((enc & 0x7f200000) == 0x0a000000)
                                        return OP_and;
                                    if ((enc & 0xffe08000) == 0x88808000)
                                        return OP_stlr;
                                } else {
                                    if ((enc & 0x7f200000) == 0x0a200000)
                                        return OP_bic;
                                    if ((enc & 0xffe0fc00) == 0x88a07c00)
                                        return OP_cas;
                                    if ((enc & 0xffe0fc00) == 0x88a0fc00)
                                        return OP_casl;
                                }
                            } else {
                                if ((enc >> 21 & 1) == 0) {
                                    if ((enc >> 25 & 1) == 0) {
                                        if ((enc & 0x9f000000) == 0x90000000)
                                            return OP_adrp;
                                        if ((enc & 0xff000000) == 0x98000000)
                                            return OP_ldrsw;
                                    } else {
                                        if ((enc & 0x7fe00c00) == 0x1a800000)
                                            return OP_csel;
                                        if ((enc & 0x7fe00c00) == 0x1a800400)
                                            return OP_csinc;
                                        if ((enc & 0xff800000) == 0x92800000)
                                            return OP_movn;
                                    }
                                } else {
                                    if ((enc >> 24 & 1) == 0) {
                                        if ((enc & 0x9f000000) == 0x90000000)
                                            return OP_adrp;
                                        if ((enc & 0xff000000) == 0x98000000)
                                            return OP_ldrsw;
                                        if ((enc & 0xff800000) == 0x92800000)
                                            return OP_movn;
                                    } else {
                                        if ((enc & 0xffe08000) == 0x9ba00000)
                                            return OP_umaddl;
                                        if ((enc & 0xffe08000) == 0x9ba08000)
                                            return OP_umsubl;
                                    }
                                }
                            }
                        } else {
                            if ((enc >> 21 & 1) == 0) {
                                if ((enc >> 28 & 1) == 0) {
                                    if ((enc >> 24 & 1) == 0) {
                                        if ((enc & 0x7f200000) == 0x2a000000)
                                            return OP_orr;
                                        if ((enc & 0xffc00000) == 0xa8800000)
                                            return OP_stp;
                                    } else {
                                        if ((enc & 0x7f200000) == 0x2b000000)
                                            return OP_adds;
                                        if ((enc & 0xffc00000) == 0xa9800000)
                                            return OP_stp;
                                    }
                                } else {
                                    if ((enc >> 10 & 1) == 0) {
                                        if ((enc >> 11 & 1) == 0) {
                                            if ((enc & 0x9f000000) == 0x90000000)
                                                return OP_adrp;
                                            if ((enc & 0xffc00000) == 0xb9800000)
                                                return OP_ldrsw;
                                            if ((enc & 0xffe00c00) == 0xb8800000)
                                                return OP_ldursw;
                                        } else {
                                            if ((enc & 0x9f000000) == 0x90000000)
                                                return OP_adrp;
                                            if ((enc & 0xffc00000) == 0xb9800000)
                                                return OP_ldrsw;
                                            if ((enc & 0xffe00c00) == 0xb8800800)
                                                return OP_ldtrsw;
                                        }
                                    } else {
                                        if ((enc >> 11 & 1) == 0) {
                                            if ((enc & 0x9f000000) == 0x90000000)
                                                return OP_adrp;
                                            if ((enc & 0xffe00c00) == 0xb8800400)
                                                return OP_ldrsw;
                                            if ((enc & 0xffc00000) == 0xb9800000)
                                                return OP_ldrsw;
                                        } else {
                                            if ((enc & 0x9f000000) == 0x90000000)
                                                return OP_adrp;
                                            if ((enc & 0xffe00c00) == 0xb8800c00)
                                                return OP_ldrsw;
                                            if ((enc & 0xffc00000) == 0xb9800000)
                                                return OP_ldrsw;
                                        }
                                    }
                                }
                            } else {
                                if ((enc >> 12 & 1) == 0) {
                                    if ((enc >> 28 & 1) == 0) {
                                        if ((enc & 0x7f200000) == 0x2a200000)
                                            return OP_orn;
                                        if ((enc & 0xffc00000) == 0xa8800000)
                                            return OP_stp;
                                        if ((enc & 0xffc00000) == 0xa9800000)
                                            return OP_stp;
                                    } else {
                                        if ((enc >> 13 & 1) == 0) {
                                            if ((enc >> 11 & 1) == 0) {
                                                if ((enc >> 14 & 1) == 0) {
                                                    if ((enc >> 15 & 1) == 0) {
                                                        if ((enc & 0x9f000000) == 0x90000000)
                                                            return OP_adrp;
                                                        if ((enc & 0xffe0fc00) == 0xb8a00000)
                                                            return OP_ldadda;
                                                        if ((enc & 0xffc00000) == 0xb9800000)
                                                            return OP_ldrsw;
                                                    } else {
                                                        if ((enc & 0x9f000000) == 0x90000000)
                                                            return OP_adrp;
                                                        if ((enc & 0xffc00000) == 0xb9800000)
                                                            return OP_ldrsw;
                                                        if ((enc & 0xffe0fc00) == 0xb8a08000)
                                                            return OP_swpa;
                                                    }
                                                } else {
                                                    if ((enc & 0x9f000000) == 0x90000000)
                                                        return OP_adrp;
                                                    if ((enc & 0xffc00000) == 0xb9800000)
                                                        return OP_ldrsw;
                                                    if ((enc & 0xffe0fc00) == 0xb8a04000)
                                                        return OP_ldsmaxa;
                                                }
                                            } else {
                                                if ((enc & 0x9f000000) == 0x90000000)
                                                    return OP_adrp;
                                                if ((enc & 0xffe00c00) == 0xb8a00800)
                                                    return OP_ldrsw;
                                                if ((enc & 0xffc00000) == 0xb9800000)
                                                    return OP_ldrsw;
                                            }
                                        } else {
                                            if ((enc >> 11 & 1) == 0) {
                                                if ((enc >> 14 & 1) == 0) {
                                                    if ((enc & 0x9f000000) == 0x90000000)
                                                        return OP_adrp;
                                                    if ((enc & 0xffe0fc00) == 0xb8a02000)
                                                        return OP_ldeora;
                                                    if ((enc & 0xffc00000) == 0xb9800000)
                                                        return OP_ldrsw;
                                                } else {
                                                    if ((enc & 0x9f000000) == 0x90000000)
                                                        return OP_adrp;
                                                    if ((enc & 0xffc00000) == 0xb9800000)
                                                        return OP_ldrsw;
                                                    if ((enc & 0xffe0fc00) == 0xb8a06000)
                                                        return OP_ldumaxa;
                                                }
                                            } else {
                                                if ((enc & 0x9f000000) == 0x90000000)
                                                    return OP_adrp;
                                                if ((enc & 0xffe00c00) == 0xb8a00800)
                                                    return OP_ldrsw;
                                                if ((enc & 0xffc00000) == 0xb9800000)
                                                    return OP_ldrsw;
                                            }
                                        }
                                    }
                                } else {
                                    if ((enc >> 28 & 1) == 0) {
                                        if ((enc & 0x7f200000) == 0x2a200000)
                                            return OP_orn;
                                        if ((enc & 0xffc00000) == 0xa8800000)
                                            return OP_stp;
                                        if ((enc & 0xffc00000) == 0xa9800000)
                                            return OP_stp;
                                    } else {
                                        if ((enc >> 13 & 1) == 0) {
                                            if ((enc >> 11 & 1) == 0) {
                                                if ((enc >> 14 & 1) == 0) {
                                                    if ((enc & 0x9f000000) == 0x90000000)
                                                        return OP_adrp;
                                                    if ((enc & 0xffe0fc00) == 0xb8a01000)
                                                        return OP_ldclra;
                                                    if ((enc & 0xffc00000) == 0xb9800000)
                                                        return OP_ldrsw;
                                                } else {
                                                    if ((enc & 0x9f000000) == 0x90000000)
                                                        return OP_adrp;
                                                    if ((enc & 0xffc00000) == 0xb9800000)
                                                        return OP_ldrsw;
                                                    if ((enc & 0xffe0fc00) == 0xb8a05000)
                                                        return OP_ldsmina;
                                                }
                                            } else {
                                                if ((enc & 0x9f000000) == 0x90000000)
                                                    return OP_adrp;
                                                if ((enc & 0xffe00c00) == 0xb8a00800)
                                                    return OP_ldrsw;
                                                if ((enc & 0xffc00000) == 0xb9800000)
                                                    return OP_ldrsw;
                                            }
                                        } else {
                                            if ((enc >> 11 & 1) == 0) {
                                                if ((enc >> 14 & 1) == 0) {
                                                    if ((enc & 0x9f000000) == 0x90000000)
                                                        return OP_adrp;
                                                    if ((enc & 0xffc00000) == 0xb9800000)
                                                        return OP_ldrsw;
                                                    if ((enc & 0xffe0fc00) == 0xb8a03000)
                                                        return OP_ldseta;
                                                } else {
                                                    if ((enc & 0x9f000000) == 0x90000000)
                                                        return OP_adrp;
                                                    if ((enc & 0xffc00000) == 0xb9800000)
                                                        return OP_ldrsw;
                                                    if ((enc & 0xffe0fc00) == 0xb8a07000)
                                                        return OP_ldumina;
                                                }
                                            } else {
                                                if ((enc & 0x9f000000) == 0x90000000)
                                                    return OP_adrp;
                                                if ((enc & 0xffe00c00) == 0xb8a00800)
                                                    return OP_ldrsw;
                                                if ((enc & 0xffc00000) == 0xb9800000)
                                                    return OP_ldrsw;
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            } else {
                if ((enc >> 23 & 1) == 0) {
                    if ((enc >> 31 & 1) == 0) {
                        if ((enc >> 25 & 1) == 0) {
                            if ((enc >> 21 & 1) == 0) {
                                if ((enc >> 29 & 1) == 0) {
                                    if ((enc >> 27 & 1) == 0) {
                                        if ((enc & 0x9f000000) == 0x10000000)
                                            return OP_adr;
                                        if ((enc & 0x7f800000) == 0x51000000)
                                            return OP_sub;
                                    } else {
                                        if ((enc & 0xff000000) == 0x58000000)
                                            return OP_ldr;
                                        if ((enc & 0xffe08000) == 0x48008000)
                                            return OP_stlxrh;
                                        if ((enc & 0xffe08000) == 0x48000000)
                                            return OP_stxrh;
                                    }
                                } else {
                                    if ((enc >> 10 & 1) == 0) {
                                        if ((enc >> 24 & 1) == 0) {
                                            if ((enc & 0x9f000000) == 0x10000000)
                                                return OP_adr;
                                            if ((enc & 0xffe00c00) == 0x78000800)
                                                return OP_sttrh;
                                            if ((enc & 0xffe00c00) == 0x78000000)
                                                return OP_sturh;
                                        } else {
                                            if ((enc & 0xffc00000) == 0x79000000)
                                                return OP_strh;
                                            if ((enc & 0x7f800000) == 0x71000000)
                                                return OP_subs;
                                        }
                                    } else {
                                        if ((enc >> 24 & 1) == 0) {
                                            if ((enc & 0x9f000000) == 0x10000000)
                                                return OP_adr;
                                            if ((enc & 0xffe00c00) == 0x78000400)
                                                return OP_strh;
                                            if ((enc & 0xffe00c00) == 0x78000c00)
                                                return OP_strh;
                                        } else {
                                            if ((enc & 0xffc00000) == 0x79000000)
                                                return OP_strh;
                                            if ((enc & 0x7f800000) == 0x71000000)
                                                return OP_subs;
                                        }
                                    }
                                }
                            } else {
                                if ((enc >> 12 & 1) == 0) {
                                    if ((enc >> 24 & 1) == 0) {
                                        if ((enc >> 13 & 1) == 0) {
                                            if ((enc >> 11 & 1) == 0) {
                                                if ((enc >> 14 & 1) == 0) {
                                                    if ((enc >> 15 & 1) == 0) {
                                                        if ((enc & 0x9f000000) == 0x10000000)
                                                            return OP_adr;
                                                        if ((enc & 0xffe0fc00) == 0x78200000)
                                                            return OP_ldaddh;
                                                        if ((enc & 0xff000000) == 0x58000000)
                                                            return OP_ldr;
                                                    } else {
                                                        if ((enc & 0x9f000000) == 0x10000000)
                                                            return OP_adr;
                                                        if ((enc & 0xff000000) == 0x58000000)
                                                            return OP_ldr;
                                                        if ((enc & 0xffe0fc00) == 0x78208000)
                                                            return OP_swph;
                                                    }
                                                } else {
                                                    if ((enc & 0x9f000000) == 0x10000000)
                                                        return OP_adr;
                                                    if ((enc & 0xff000000) == 0x58000000)
                                                        return OP_ldr;
                                                    if ((enc & 0xffe0fc00) == 0x78204000)
                                                        return OP_ldsmaxh;
                                                }
                                            } else {
                                                if ((enc & 0x9f000000) == 0x10000000)
                                                    return OP_adr;
                                                if ((enc & 0xff000000) == 0x58000000)
                                                    return OP_ldr;
                                                if ((enc & 0xffe00c00) == 0x78200800)
                                                    return OP_strh;
                                            }
                                        } else {
                                            if ((enc >> 11 & 1) == 0) {
                                                if ((enc >> 14 & 1) == 0) {
                                                    if ((enc & 0x9f000000) == 0x10000000)
                                                        return OP_adr;
                                                    if ((enc & 0xffe0fc00) == 0x78202000)
                                                        return OP_ldeorh;
                                                    if ((enc & 0xff000000) == 0x58000000)
                                                        return OP_ldr;
                                                } else {
                                                    if ((enc & 0x9f000000) == 0x10000000)
                                                        return OP_adr;
                                                    if ((enc & 0xff000000) == 0x58000000)
                                                        return OP_ldr;
                                                    if ((enc & 0xffe0fc00) == 0x78206000)
                                                        return OP_ldumaxh;
                                                }
                                            } else {
                                                if ((enc & 0x9f000000) == 0x10000000)
                                                    return OP_adr;
                                                if ((enc & 0xff000000) == 0x58000000)
                                                    return OP_ldr;
                                                if ((enc & 0xffe00c00) == 0x78200800)
                                                    return OP_strh;
                                            }
                                        }
                                    } else {
                                        if ((enc & 0xffc00000) == 0x79000000)
                                            return OP_strh;
                                        if ((enc & 0x7f800000) == 0x51000000)
                                            return OP_sub;
                                        if ((enc & 0x7f800000) == 0x71000000)
                                            return OP_subs;
                                    }
                                } else {
                                    if ((enc >> 29 & 1) == 0) {
                                        if ((enc >> 27 & 1) == 0) {
                                            if ((enc & 0x9f000000) == 0x10000000)
                                                return OP_adr;
                                            if ((enc & 0x7f800000) == 0x51000000)
                                                return OP_sub;
                                        } else {
                                            if ((enc & 0xffe0fc00) == 0x48207c00)
                                                return OP_casp;
                                            if ((enc & 0xffe0fc00) == 0x4820fc00)
                                                return OP_caspl;
                                            if ((enc & 0xff000000) == 0x58000000)
                                                return OP_ldr;
                                        }
                                    } else {
                                        if ((enc >> 13 & 1) == 0) {
                                            if ((enc >> 24 & 1) == 0) {
                                                if ((enc >> 11 & 1) == 0) {
                                                    if ((enc & 0x9f000000) == 0x10000000)
                                                        return OP_adr;
                                                    if ((enc & 0xffe0fc00) == 0x78201000)
                                                        return OP_ldclrh;
                                                    if ((enc & 0xffe0fc00) == 0x78205000)
                                                        return OP_ldsminh;
                                                } else {
                                                    if ((enc & 0x9f000000) == 0x10000000)
                                                        return OP_adr;
                                                    if ((enc & 0xffe00c00) == 0x78200800)
                                                        return OP_strh;
                                                }
                                            } else {
                                                if ((enc & 0xffc00000) == 0x79000000)
                                                    return OP_strh;
                                                if ((enc & 0x7f800000) == 0x71000000)
                                                    return OP_subs;
                                            }
                                        } else {
                                            if ((enc >> 24 & 1) == 0) {
                                                if ((enc >> 11 & 1) == 0) {
                                                    if ((enc & 0x9f000000) == 0x10000000)
                                                        return OP_adr;
                                                    if ((enc & 0xffe0fc00) == 0x78203000)
                                                        return OP_ldseth;
                                                    if ((enc & 0xffe0fc00) == 0x78207000)
                                                        return OP_lduminh;
                                                } else {
                                                    if ((enc & 0x9f000000) == 0x10000000)
                                                        return OP_adr;
                                                    if ((enc & 0xffe00c00) == 0x78200800)
                                                        return OP_strh;
                                                }
                                            } else {
                                                if ((enc & 0xffc00000) == 0x79000000)
                                                    return OP_strh;
                                                if ((enc & 0x7f800000) == 0x71000000)
                                                    return OP_subs;
                                            }
                                        }
                                    }
                                }
                            }
                        } else {
                            if ((enc >> 29 & 1) == 0) {
                                if ((enc >> 24 & 1) == 0) {
                                    if ((enc >> 28 & 1) == 0) {
                                        if ((enc & 0x7f200000) == 0x4a200000)
                                            return OP_eon;
                                        if ((enc & 0x7f200000) == 0x4a000000)
                                            return OP_eor;
                                    } else {
                                        if ((enc & 0x7f800000) == 0x52000000)
                                            return OP_eor;
                                        if ((enc & 0x7fe0fc00) == 0x5a000000)
                                            return OP_sbc;
                                    }
                                } else {
                                    if ((enc & 0x7f200000) == 0x4b000000)
                                        return OP_sub;
                                    if ((enc & 0x7fe00000) == 0x4b200000)
                                        return OP_sub;
                                    if ((enc & 0xffc00000) == 0x53000000)
                                        return OP_ubfm;
                                }
                            } else {
                                if ((enc >> 21 & 1) == 0) {
                                    if ((enc >> 28 & 1) == 0) {
                                        if ((enc & 0x7f200000) == 0x6a000000)
                                            return OP_ands;
                                        if ((enc & 0x7f200000) == 0x6b000000)
                                            return OP_subs;
                                    } else {
                                        if ((enc & 0x7f800000) == 0x72000000)
                                            return OP_ands;
                                        if ((enc & 0x7fe0fc00) == 0x7a000000)
                                            return OP_sbcs;
                                    }
                                } else {
                                    if ((enc & 0x7f800000) == 0x72000000)
                                        return OP_ands;
                                    if ((enc & 0x7f200000) == 0x6a200000)
                                        return OP_bics;
                                    if ((enc & 0x7fe00000) == 0x6b200000)
                                        return OP_subs;
                                }
                            }
                        }
                    } else {
                        if ((enc >> 21 & 1) == 0) {
                            if ((enc >> 25 & 1) == 0) {
                                if ((enc >> 29 & 1) == 0) {
                                    if ((enc >> 27 & 1) == 0) {
                                        if ((enc & 0x9f000000) == 0x90000000)
                                            return OP_adrp;
                                        if ((enc & 0x7f800000) == 0x51000000)
                                            return OP_sub;
                                    } else {
                                        if ((enc & 0xff000000) == 0xd8000000)
                                            return OP_prfm;
                                        if ((enc & 0xffe08000) == 0xc8008000)
                                            return OP_stlxr;
                                        if ((enc & 0xffe08000) == 0xc8000000)
                                            return OP_stxr;
                                    }
                                } else {
                                    if ((enc >> 10 & 1) == 0) {
                                        if ((enc >> 24 & 1) == 0) {
                                            if ((enc & 0x9f000000) == 0x90000000)
                                                return OP_adrp;
                                            if ((enc & 0xffe00c00) == 0xf8000800)
                                                return OP_sttr;
                                            if ((enc & 0xffe00c00) == 0xf8000000)
                                                return OP_stur;
                                        } else {
                                            if ((enc & 0xffc00000) == 0xf9000000)
                                                return OP_str;
                                            if ((enc & 0x7f800000) == 0x71000000)
                                                return OP_subs;
                                        }
                                    } else {
                                        if ((enc >> 24 & 1) == 0) {
                                            if ((enc & 0x9f000000) == 0x90000000)
                                                return OP_adrp;
                                            if ((enc & 0xffe00c00) == 0xf8000400)
                                                return OP_str;
                                            if ((enc & 0xffe00c00) == 0xf8000c00)
                                                return OP_str;
                                        } else {
                                            if ((enc & 0xffc00000) == 0xf9000000)
                                                return OP_str;
                                            if ((enc & 0x7f800000) == 0x71000000)
                                                return OP_subs;
                                        }
                                    }
                                }
                            } else {
                                if ((enc >> 28 & 1) == 0) {
                                    if ((enc >> 24 & 1) == 0) {
                                        if ((enc & 0x7f200000) == 0x6a000000)
                                            return OP_ands;
                                        if ((enc & 0x7f200000) == 0x4a000000)
                                            return OP_eor;
                                    } else {
                                        if ((enc & 0x7f200000) == 0x4b000000)
                                            return OP_sub;
                                        if ((enc & 0x7f200000) == 0x6b000000)
                                            return OP_subs;
                                    }
                                } else {
                                    if ((enc >> 27 & 1) == 0) {
                                        if ((enc & 0x7f800000) == 0x72000000)
                                            return OP_ands;
                                        if ((enc & 0x7f800000) == 0x52000000)
                                            return OP_eor;
                                    } else {
                                        if ((enc & 0x7fe0fc00) == 0x5a000000)
                                            return OP_sbc;
                                        if ((enc & 0x7fe0fc00) == 0x7a000000)
                                            return OP_sbcs;
                                    }
                                }
                            }
                        } else {
                            if ((enc >> 29 & 1) == 0) {
                                if ((enc >> 28 & 1) == 0) {
                                    if ((enc >> 25 & 1) == 0) {
                                        if ((enc & 0xffe08000) == 0xc8208000)
                                            return OP_stlxp;
                                        if ((enc & 0xffe08000) == 0xc8200000)
                                            return OP_stxp;
                                    } else {
                                        if ((enc & 0x7f200000) == 0x4a200000)
                                            return OP_eon;
                                        if ((enc & 0x7fe00000) == 0x4b200000)
                                            return OP_sub;
                                    }
                                } else {
                                    if ((enc >> 24 & 1) == 0) {
                                        if ((enc & 0x9f000000) == 0x90000000)
                                            return OP_adrp;
                                        if ((enc & 0x7f800000) == 0x52000000)
                                            return OP_eor;
                                        if ((enc & 0xff000000) == 0xd8000000)
                                            return OP_prfm;
                                    } else {
                                        if ((enc & 0x7f800000) == 0x51000000)
                                            return OP_sub;
                                    }
                                }
                            } else {
                                if ((enc >> 12 & 1) == 0) {
                                    if ((enc >> 24 & 1) == 0) {
                                        if ((enc >> 13 & 1) == 0) {
                                            if ((enc >> 25 & 1) == 0) {
                                                if ((enc >> 11 & 1) == 0) {
                                                    if ((enc >> 14 & 1) == 0) {
                                                        if ((enc & 0x9f000000) == 0x90000000)
                                                            return OP_adrp;
                                                        if ((enc & 0xffe0fc00) == 0xf8200000)
                                                            return OP_ldadd;
                                                        if ((enc & 0xffe0fc00) == 0xf8208000)
                                                            return OP_swp;
                                                    } else {
                                                        if ((enc & 0x9f000000) == 0x90000000)
                                                            return OP_adrp;
                                                        if ((enc & 0xffe0fc00) == 0xf8204000)
                                                            return OP_ldsmax;
                                                    }
                                                } else {
                                                    if ((enc & 0x9f000000) == 0x90000000)
                                                        return OP_adrp;
                                                    if ((enc & 0xffe00c00) == 0xf8200800)
                                                        return OP_str;
                                                }
                                            } else {
                                                if ((enc & 0x7f800000) == 0x72000000)
                                                    return OP_ands;
                                                if ((enc & 0x7f200000) == 0x6a200000)
                                                    return OP_bics;
                                            }
                                        } else {
                                            if ((enc >> 25 & 1) == 0) {
                                                if ((enc >> 11 & 1) == 0) {
                                                    if ((enc & 0x9f000000) == 0x90000000)
                                                        return OP_adrp;
                                                    if ((enc & 0xffe0fc00) == 0xf8202000)
                                                        return OP_ldeor;
                                                    if ((enc & 0xffe0fc00) == 0xf8206000)
                                                        return OP_ldumax;
                                                } else {
                                                    if ((enc & 0x9f000000) == 0x90000000)
                                                        return OP_adrp;
                                                    if ((enc & 0xffe00c00) == 0xf8200800)
                                                        return OP_str;
                                                }
                                            } else {
                                                if ((enc & 0x7f800000) == 0x72000000)
                                                    return OP_ands;
                                                if ((enc & 0x7f200000) == 0x6a200000)
                                                    return OP_bics;
                                            }
                                        }
                                    } else {
                                        if ((enc & 0xffc00000) == 0xf9000000)
                                            return OP_str;
                                        if ((enc & 0x7fe00000) == 0x6b200000)
                                            return OP_subs;
                                        if ((enc & 0x7f800000) == 0x71000000)
                                            return OP_subs;
                                    }
                                } else {
                                    if ((enc >> 24 & 1) == 0) {
                                        if ((enc >> 13 & 1) == 0) {
                                            if ((enc >> 25 & 1) == 0) {
                                                if ((enc >> 11 & 1) == 0) {
                                                    if ((enc & 0x9f000000) == 0x90000000)
                                                        return OP_adrp;
                                                    if ((enc & 0xffe0fc00) == 0xf8201000)
                                                        return OP_ldclr;
                                                    if ((enc & 0xffe0fc00) == 0xf8205000)
                                                        return OP_ldsmin;
                                                } else {
                                                    if ((enc & 0x9f000000) == 0x90000000)
                                                        return OP_adrp;
                                                    if ((enc & 0xffe00c00) == 0xf8200800)
                                                        return OP_str;
                                                }
                                            } else {
                                                if ((enc & 0x7f800000) == 0x72000000)
                                                    return OP_ands;
                                                if ((enc & 0x7f200000) == 0x6a200000)
                                                    return OP_bics;
                                            }
                                        } else {
                                            if ((enc >> 25 & 1) == 0) {
                                                if ((enc >> 11 & 1) == 0) {
                                                    if ((enc & 0x9f000000) == 0x90000000)
                                                        return OP_adrp;
                                                    if ((enc & 0xffe0fc00) == 0xf8203000)
                                                        return OP_ldset;
                                                    if ((enc & 0xffe0fc00) == 0xf8207000)
                                                        return OP_ldumin;
                                                } else {
                                                    if ((enc & 0x9f000000) == 0x90000000)
                                                        return OP_adrp;
                                                    if ((enc & 0xffe00c00) == 0xf8200800)
                                                        return OP_str;
                                                }
                                            } else {
                                                if ((enc & 0x7f800000) == 0x72000000)
                                                    return OP_ands;
                                                if ((enc & 0x7f200000) == 0x6a200000)
                                                    return OP_bics;
                                            }
                                        }
                                    } else {
                                        if ((enc & 0xffc00000) == 0xf9000000)
                                            return OP_str;
                                        if ((enc & 0x7fe00000) == 0x6b200000)
                                            return OP_subs;
                                        if ((enc & 0x7f800000) == 0x71000000)
                                            return OP_subs;
                                    }
                                }
                            }
                        }
                    }
                } else {
                    if ((enc >> 31 & 1) == 0) {
                        if ((enc >> 21 & 1) == 0) {
                            if ((enc >> 25 & 1) == 0) {
                                if ((enc >> 10 & 1) == 0) {
                                    if ((enc >> 29 & 1) == 0) {
                                        if ((enc & 0x9f000000) == 0x10000000)
                                            return OP_adr;
                                        if ((enc & 0xff000000) == 0x58000000)
                                            return OP_ldr;
                                        if ((enc & 0xffe08000) == 0x48808000)
                                            return OP_stlrh;
                                    } else {
                                        if ((enc >> 11 & 1) == 0) {
                                            if ((enc & 0x9f000000) == 0x10000000)
                                                return OP_adr;
                                            if ((enc & 0xffc00000) == 0x79800000)
                                                return OP_ldrsh;
                                            if ((enc & 0xffe00c00) == 0x78800000)
                                                return OP_ldursh;
                                        } else {
                                            if ((enc & 0x9f000000) == 0x10000000)
                                                return OP_adr;
                                            if ((enc & 0xffc00000) == 0x79800000)
                                                return OP_ldrsh;
                                            if ((enc & 0xffe00c00) == 0x78800800)
                                                return OP_ldtrsh;
                                        }
                                    }
                                } else {
                                    if ((enc >> 29 & 1) == 0) {
                                        if ((enc & 0x9f000000) == 0x10000000)
                                            return OP_adr;
                                        if ((enc & 0xff000000) == 0x58000000)
                                            return OP_ldr;
                                        if ((enc & 0xffe08000) == 0x48808000)
                                            return OP_stlrh;
                                    } else {
                                        if ((enc >> 11 & 1) == 0) {
                                            if ((enc & 0x9f000000) == 0x10000000)
                                                return OP_adr;
                                            if ((enc & 0xffe00c00) == 0x78800400)
                                                return OP_ldrsh;
                                            if ((enc & 0xffc00000) == 0x79800000)
                                                return OP_ldrsh;
                                        } else {
                                            if ((enc & 0x9f000000) == 0x10000000)
                                                return OP_adr;
                                            if ((enc & 0xffe00c00) == 0x78800c00)
                                                return OP_ldrsh;
                                            if ((enc & 0xffc00000) == 0x79800000)
                                                return OP_ldrsh;
                                        }
                                    }
                                }
                            } else {
                                if ((enc >> 28 & 1) == 0) {
                                    if ((enc >> 24 & 1) == 0) {
                                        if ((enc & 0x7f200000) == 0x6a000000)
                                            return OP_ands;
                                        if ((enc & 0x7f200000) == 0x4a000000)
                                            return OP_eor;
                                    } else {
                                        if ((enc & 0x7f200000) == 0x4b000000)
                                            return OP_sub;
                                        if ((enc & 0x7f200000) == 0x6b000000)
                                            return OP_subs;
                                    }
                                } else {
                                    if ((enc >> 27 & 1) == 0) {
                                        if ((enc & 0xff800000) == 0x72800000)
                                            return OP_movk;
                                        if ((enc & 0xff800000) == 0x52800000)
                                            return OP_movz;
                                    } else {
                                        if ((enc & 0x7fe00c00) == 0x5a800000)
                                            return OP_csinv;
                                        if ((enc & 0x7fe00c00) == 0x5a800400)
                                            return OP_csneg;
                                    }
                                }
                            }
                        } else {
                            if ((enc >> 12 & 1) == 0) {
                                if ((enc >> 25 & 1) == 0) {
                                    if ((enc >> 13 & 1) == 0) {
                                        if ((enc >> 11 & 1) == 0) {
                                            if ((enc >> 14 & 1) == 0) {
                                                if ((enc >> 15 & 1) == 0) {
                                                    if ((enc >> 24 & 1) == 0) {
                                                        if ((enc & 0x9f000000) == 0x10000000)
                                                            return OP_adr;
                                                        if ((enc & 0xffe0fc00) == 0x78a00000)
                                                            return OP_ldaddah;
                                                        if ((enc & 0xff000000) == 0x58000000)
                                                            return OP_ldr;
                                                    } else {
                                                        if ((enc & 0xffc00000) == 0x79800000)
                                                            return OP_ldrsh;
                                                    }
                                                } else {
                                                    if ((enc >> 24 & 1) == 0) {
                                                        if ((enc & 0x9f000000) == 0x10000000)
                                                            return OP_adr;
                                                        if ((enc & 0xff000000) == 0x58000000)
                                                            return OP_ldr;
                                                        if ((enc & 0xffe0fc00) == 0x78a08000)
                                                            return OP_swpah;
                                                    } else {
                                                        if ((enc & 0xffc00000) == 0x79800000)
                                                            return OP_ldrsh;
                                                    }
                                                }
                                            } else {
                                                if ((enc >> 24 & 1) == 0) {
                                                    if ((enc & 0x9f000000) == 0x10000000)
                                                        return OP_adr;
                                                    if ((enc & 0xff000000) == 0x58000000)
                                                        return OP_ldr;
                                                    if ((enc & 0xffe0fc00) == 0x78a04000)
                                                        return OP_ldsmaxah;
                                                } else {
                                                    if ((enc & 0xffc00000) == 0x79800000)
                                                        return OP_ldrsh;
                                                }
                                            }
                                        } else {
                                            if ((enc >> 24 & 1) == 0) {
                                                if ((enc & 0x9f000000) == 0x10000000)
                                                    return OP_adr;
                                                if ((enc & 0xff000000) == 0x58000000)
                                                    return OP_ldr;
                                                if ((enc & 0xffe00c00) == 0x78a00800)
                                                    return OP_ldrsh;
                                            } else {
                                                if ((enc & 0xffc00000) == 0x79800000)
                                                    return OP_ldrsh;
                                            }
                                        }
                                    } else {
                                        if ((enc >> 11 & 1) == 0) {
                                            if ((enc >> 14 & 1) == 0) {
                                                if ((enc >> 24 & 1) == 0) {
                                                    if ((enc & 0x9f000000) == 0x10000000)
                                                        return OP_adr;
                                                    if ((enc & 0xffe0fc00) == 0x78a02000)
                                                        return OP_ldeorah;
                                                    if ((enc & 0xff000000) == 0x58000000)
                                                        return OP_ldr;
                                                } else {
                                                    if ((enc & 0xffc00000) == 0x79800000)
                                                        return OP_ldrsh;
                                                }
                                            } else {
                                                if ((enc >> 24 & 1) == 0) {
                                                    if ((enc & 0x9f000000) == 0x10000000)
                                                        return OP_adr;
                                                    if ((enc & 0xff000000) == 0x58000000)
                                                        return OP_ldr;
                                                    if ((enc & 0xffe0fc00) == 0x78a06000)
                                                        return OP_ldumaxah;
                                                } else {
                                                    if ((enc & 0xffc00000) == 0x79800000)
                                                        return OP_ldrsh;
                                                }
                                            }
                                        } else {
                                            if ((enc >> 24 & 1) == 0) {
                                                if ((enc & 0x9f000000) == 0x10000000)
                                                    return OP_adr;
                                                if ((enc & 0xff000000) == 0x58000000)
                                                    return OP_ldr;
                                                if ((enc & 0xffe00c00) == 0x78a00800)
                                                    return OP_ldrsh;
                                            } else {
                                                if ((enc & 0xffc00000) == 0x79800000)
                                                    return OP_ldrsh;
                                            }
                                        }
                                    }
                                } else {
                                    if ((enc >> 27 & 1) == 0) {
                                        if ((enc & 0xff800000) == 0x72800000)
                                            return OP_movk;
                                        if ((enc & 0xff800000) == 0x52800000)
                                            return OP_movz;
                                    } else {
                                        if ((enc & 0x7f200000) == 0x6a200000)
                                            return OP_bics;
                                        if ((enc & 0x7f200000) == 0x4a200000)
                                            return OP_eon;
                                    }
                                }
                            } else {
                                if ((enc >> 29 & 1) == 0) {
                                    if ((enc >> 28 & 1) == 0) {
                                        if ((enc & 0xffe0fc00) == 0x48a07c00)
                                            return OP_cash;
                                        if ((enc & 0xffe0fc00) == 0x48a0fc00)
                                            return OP_caslh;
                                        if ((enc & 0x7f200000) == 0x4a200000)
                                            return OP_eon;
                                    } else {
                                        if ((enc & 0x9f000000) == 0x10000000)
                                            return OP_adr;
                                        if ((enc & 0xff000000) == 0x58000000)
                                            return OP_ldr;
                                        if ((enc & 0xff800000) == 0x52800000)
                                            return OP_movz;
                                    }
                                } else {
                                    if ((enc >> 13 & 1) == 0) {
                                        if ((enc >> 25 & 1) == 0) {
                                            if ((enc >> 11 & 1) == 0) {
                                                if ((enc >> 14 & 1) == 0) {
                                                    if ((enc & 0x9f000000) == 0x10000000)
                                                        return OP_adr;
                                                    if ((enc & 0xffe0fc00) == 0x78a01000)
                                                        return OP_ldclrah;
                                                    if ((enc & 0xffc00000) == 0x79800000)
                                                        return OP_ldrsh;
                                                } else {
                                                    if ((enc & 0x9f000000) == 0x10000000)
                                                        return OP_adr;
                                                    if ((enc & 0xffc00000) == 0x79800000)
                                                        return OP_ldrsh;
                                                    if ((enc & 0xffe0fc00) == 0x78a05000)
                                                        return OP_ldsminah;
                                                }
                                            } else {
                                                if ((enc & 0x9f000000) == 0x10000000)
                                                    return OP_adr;
                                                if ((enc & 0xffe00c00) == 0x78a00800)
                                                    return OP_ldrsh;
                                                if ((enc & 0xffc00000) == 0x79800000)
                                                    return OP_ldrsh;
                                            }
                                        } else {
                                            if ((enc & 0x7f200000) == 0x6a200000)
                                                return OP_bics;
                                            if ((enc & 0xff800000) == 0x72800000)
                                                return OP_movk;
                                        }
                                    } else {
                                        if ((enc >> 25 & 1) == 0) {
                                            if ((enc >> 11 & 1) == 0) {
                                                if ((enc >> 14 & 1) == 0) {
                                                    if ((enc & 0x9f000000) == 0x10000000)
                                                        return OP_adr;
                                                    if ((enc & 0xffc00000) == 0x79800000)
                                                        return OP_ldrsh;
                                                    if ((enc & 0xffe0fc00) == 0x78a03000)
                                                        return OP_ldsetah;
                                                } else {
                                                    if ((enc & 0x9f000000) == 0x10000000)
                                                        return OP_adr;
                                                    if ((enc & 0xffc00000) == 0x79800000)
                                                        return OP_ldrsh;
                                                    if ((enc & 0xffe0fc00) == 0x78a07000)
                                                        return OP_lduminah;
                                                }
                                            } else {
                                                if ((enc & 0x9f000000) == 0x10000000)
                                                    return OP_adr;
                                                if ((enc & 0xffe00c00) == 0x78a00800)
                                                    return OP_ldrsh;
                                                if ((enc & 0xffc00000) == 0x79800000)
                                                    return OP_ldrsh;
                                            }
                                        } else {
                                            if ((enc & 0x7f200000) == 0x6a200000)
                                                return OP_bics;
                                            if ((enc & 0xff800000) == 0x72800000)
                                                return OP_movk;
                                        }
                                    }
                                }
                            }
                        }
                    } else {
                        if ((enc >> 25 & 1) == 0) {
                            if ((enc >> 12 & 1) == 0) {
                                if ((enc >> 13 & 1) == 0) {
                                    if ((enc >> 15 & 1) == 0) {
                                        if ((enc >> 11 & 1) == 0) {
                                            if ((enc >> 14 & 1) == 0) {
                                                if ((enc >> 21 & 1) == 0) {
                                                    if ((enc >> 24 & 1) == 0) {
                                                        if ((enc & 0x9f000000) == 0x90000000)
                                                            return OP_adrp;
                                                        if ((enc & 0xff000000) == 0xd8000000)
                                                            return OP_prfm;
                                                        if ((enc & 0xffe00c00) == 0xf8800000)
                                                            return OP_prfum;
                                                    } else {
                                                        if ((enc & 0xffc00000) == 0xf9800000)
                                                            return OP_prfm;
                                                    }
                                                } else {
                                                    if ((enc >> 24 & 1) == 0) {
                                                        if ((enc & 0x9f000000) == 0x90000000)
                                                            return OP_adrp;
                                                        if ((enc & 0xffe0fc00) == 0xf8a00000)
                                                            return OP_ldadda;
                                                        if ((enc & 0xff000000) == 0xd8000000)
                                                            return OP_prfm;
                                                    } else {
                                                        if ((enc & 0xffc00000) == 0xf9800000)
                                                            return OP_prfm;
                                                    }
                                                }
                                            } else {
                                                if ((enc >> 21 & 1) == 0) {
                                                    if ((enc >> 24 & 1) == 0) {
                                                        if ((enc & 0x9f000000) == 0x90000000)
                                                            return OP_adrp;
                                                        if ((enc & 0xff000000) == 0xd8000000)
                                                            return OP_prfm;
                                                        if ((enc & 0xffe00c00) == 0xf8800000)
                                                            return OP_prfum;
                                                    } else {
                                                        if ((enc & 0xffc00000) == 0xf9800000)
                                                            return OP_prfm;
                                                    }
                                                } else {
                                                    if ((enc >> 24 & 1) == 0) {
                                                        if ((enc & 0x9f000000) == 0x90000000)
                                                            return OP_adrp;
                                                        if ((enc & 0xffe0fc00) == 0xf8a04000)
                                                            return OP_ldsmaxa;
                                                        if ((enc & 0xff000000) == 0xd8000000)
                                                            return OP_prfm;
                                                    } else {
                                                        if ((enc & 0xffc00000) == 0xf9800000)
                                                            return OP_prfm;
                                                    }
                                                }
                                            }
                                        } else {
                                            if ((enc >> 24 & 1) == 0) {
                                                if ((enc & 0x9f000000) == 0x90000000)
                                                    return OP_adrp;
                                                if ((enc & 0xff000000) == 0xd8000000)
                                                    return OP_prfm;
                                                if ((enc & 0xffe00c00) == 0xf8a00800)
                                                    return OP_prfm;
                                            } else {
                                                if ((enc & 0xffc00000) == 0xf9800000)
                                                    return OP_prfm;
                                            }
                                        }
                                    } else {
                                        if ((enc >> 21 & 1) == 0) {
                                            if ((enc >> 29 & 1) == 0) {
                                                if ((enc & 0x9f000000) == 0x90000000)
                                                    return OP_adrp;
                                                if ((enc & 0xff000000) == 0xd8000000)
                                                    return OP_prfm;
                                                if ((enc & 0xffe08000) == 0xc8808000)
                                                    return OP_stlr;
                                            } else {
                                                if ((enc & 0x9f000000) == 0x90000000)
                                                    return OP_adrp;
                                                if ((enc & 0xffc00000) == 0xf9800000)
                                                    return OP_prfm;
                                                if ((enc & 0xffe00c00) == 0xf8800000)
                                                    return OP_prfum;
                                            }
                                        } else {
                                            if ((enc >> 11 & 1) == 0) {
                                                if ((enc >> 24 & 1) == 0) {
                                                    if ((enc & 0x9f000000) == 0x90000000)
                                                        return OP_adrp;
                                                    if ((enc & 0xff000000) == 0xd8000000)
                                                        return OP_prfm;
                                                    if ((enc & 0xffe0fc00) == 0xf8a08000)
                                                        return OP_swpa;
                                                } else {
                                                    if ((enc & 0xffc00000) == 0xf9800000)
                                                        return OP_prfm;
                                                }
                                            } else {
                                                if ((enc >> 24 & 1) == 0) {
                                                    if ((enc & 0x9f000000) == 0x90000000)
                                                        return OP_adrp;
                                                    if ((enc & 0xff000000) == 0xd8000000)
                                                        return OP_prfm;
                                                    if ((enc & 0xffe00c00) == 0xf8a00800)
                                                        return OP_prfm;
                                                } else {
                                                    if ((enc & 0xffc00000) == 0xf9800000)
                                                        return OP_prfm;
                                                }
                                            }
                                        }
                                    }
                                } else {
                                    if ((enc >> 21 & 1) == 0) {
                                        if ((enc >> 29 & 1) == 0) {
                                            if ((enc & 0x9f000000) == 0x90000000)
                                                return OP_adrp;
                                            if ((enc & 0xff000000) == 0xd8000000)
                                                return OP_prfm;
                                            if ((enc & 0xffe08000) == 0xc8808000)
                                                return OP_stlr;
                                        } else {
                                            if ((enc & 0x9f000000) == 0x90000000)
                                                return OP_adrp;
                                            if ((enc & 0xffc00000) == 0xf9800000)
                                                return OP_prfm;
                                            if ((enc & 0xffe00c00) == 0xf8800000)
                                                return OP_prfum;
                                        }
                                    } else {
                                        if ((enc >> 11 & 1) == 0) {
                                            if ((enc >> 14 & 1) == 0) {
                                                if ((enc >> 24 & 1) == 0) {
                                                    if ((enc & 0x9f000000) == 0x90000000)
                                                        return OP_adrp;
                                                    if ((enc & 0xffe0fc00) == 0xf8a02000)
                                                        return OP_ldeora;
                                                    if ((enc & 0xff000000) == 0xd8000000)
                                                        return OP_prfm;
                                                } else {
                                                    if ((enc & 0xffc00000) == 0xf9800000)
                                                        return OP_prfm;
                                                }
                                            } else {
                                                if ((enc >> 24 & 1) == 0) {
                                                    if ((enc & 0x9f000000) == 0x90000000)
                                                        return OP_adrp;
                                                    if ((enc & 0xffe0fc00) == 0xf8a06000)
                                                        return OP_ldumaxa;
                                                    if ((enc & 0xff000000) == 0xd8000000)
                                                        return OP_prfm;
                                                } else {
                                                    if ((enc & 0xffc00000) == 0xf9800000)
                                                        return OP_prfm;
                                                }
                                            }
                                        } else {
                                            if ((enc >> 24 & 1) == 0) {
                                                if ((enc & 0x9f000000) == 0x90000000)
                                                    return OP_adrp;
                                                if ((enc & 0xff000000) == 0xd8000000)
                                                    return OP_prfm;
                                                if ((enc & 0xffe00c00) == 0xf8a00800)
                                                    return OP_prfm;
                                            } else {
                                                if ((enc & 0xffc00000) == 0xf9800000)
                                                    return OP_prfm;
                                            }
                                        }
                                    }
                                }
                            } else {
                                if ((enc >> 29 & 1) == 0) {
                                    if ((enc >> 28 & 1) == 0) {
                                        if ((enc & 0xffe0fc00) == 0xc8a07c00)
                                            return OP_cas;
                                        if ((enc & 0xffe0fc00) == 0xc8a0fc00)
                                            return OP_casl;
                                        if ((enc & 0xffe08000) == 0xc8808000)
                                            return OP_stlr;
                                    } else {
                                        if ((enc & 0x9f000000) == 0x90000000)
                                            return OP_adrp;
                                        if ((enc & 0xff000000) == 0xd8000000)
                                            return OP_prfm;
                                    }
                                } else {
                                    if ((enc >> 13 & 1) == 0) {
                                        if ((enc >> 11 & 1) == 0) {
                                            if ((enc >> 14 & 1) == 0) {
                                                if ((enc >> 21 & 1) == 0) {
                                                    if ((enc & 0x9f000000) == 0x90000000)
                                                        return OP_adrp;
                                                    if ((enc & 0xffc00000) == 0xf9800000)
                                                        return OP_prfm;
                                                    if ((enc & 0xffe00c00) == 0xf8800000)
                                                        return OP_prfum;
                                                } else {
                                                    if ((enc & 0x9f000000) == 0x90000000)
                                                        return OP_adrp;
                                                    if ((enc & 0xffe0fc00) == 0xf8a01000)
                                                        return OP_ldclra;
                                                    if ((enc & 0xffc00000) == 0xf9800000)
                                                        return OP_prfm;
                                                }
                                            } else {
                                                if ((enc >> 21 & 1) == 0) {
                                                    if ((enc & 0x9f000000) == 0x90000000)
                                                        return OP_adrp;
                                                    if ((enc & 0xffc00000) == 0xf9800000)
                                                        return OP_prfm;
                                                    if ((enc & 0xffe00c00) == 0xf8800000)
                                                        return OP_prfum;
                                                } else {
                                                    if ((enc & 0x9f000000) == 0x90000000)
                                                        return OP_adrp;
                                                    if ((enc & 0xffe0fc00) == 0xf8a05000)
                                                        return OP_ldsmina;
                                                    if ((enc & 0xffc00000) == 0xf9800000)
                                                        return OP_prfm;
                                                }
                                            }
                                        } else {
                                            if ((enc & 0x9f000000) == 0x90000000)
                                                return OP_adrp;
                                            if ((enc & 0xffe00c00) == 0xf8a00800)
                                                return OP_prfm;
                                            if ((enc & 0xffc00000) == 0xf9800000)
                                                return OP_prfm;
                                        }
                                    } else {
                                        if ((enc >> 11 & 1) == 0) {
                                            if ((enc >> 14 & 1) == 0) {
                                                if ((enc >> 21 & 1) == 0) {
                                                    if ((enc & 0x9f000000) == 0x90000000)
                                                        return OP_adrp;
                                                    if ((enc & 0xffc00000) == 0xf9800000)
                                                        return OP_prfm;
                                                    if ((enc & 0xffe00c00) == 0xf8800000)
                                                        return OP_prfum;
                                                } else {
                                                    if ((enc & 0x9f000000) == 0x90000000)
                                                        return OP_adrp;
                                                    if ((enc & 0xffe0fc00) == 0xf8a03000)
                                                        return OP_ldseta;
                                                    if ((enc & 0xffc00000) == 0xf9800000)
                                                        return OP_prfm;
                                                }
                                            } else {
                                                if ((enc >> 21 & 1) == 0) {
                                                    if ((enc & 0x9f000000) == 0x90000000)
                                                        return OP_adrp;
                                                    if ((enc & 0xffc00000) == 0xf9800000)
                                                        return OP_prfm;
                                                    if ((enc & 0xffe00c00) == 0xf8800000)
                                                        return OP_prfum;
                                                } else {
                                                    if ((enc & 0x9f000000) == 0x90000000)
                                                        return OP_adrp;
                                                    if ((enc & 0xffe0fc00) == 0xf8a07000)
                                                        return OP_ldumina;
                                                    if ((enc & 0xffc00000) == 0xf9800000)
                                                        return OP_prfm;
                                                }
                                            }
                                        } else {
                                            if ((enc & 0x9f000000) == 0x90000000)
                                                return OP_adrp;
                                            if ((enc & 0xffe00c00) == 0xf8a00800)
                                                return OP_prfm;
                                            if ((enc & 0xffc00000) == 0xf9800000)
                                                return OP_prfm;
                                        }
                                    }
                                }
                            }
                        } else {
                            if ((enc >> 28 & 1) == 0) {
                                if ((enc >> 29 & 1) == 0) {
                                    if ((enc & 0x7f200000) == 0x4a200000)
                                        return OP_eon;
                                    if ((enc & 0x7f200000) == 0x4a000000)
                                        return OP_eor;
                                    if ((enc & 0x7f200000) == 0x4b000000)
                                        return OP_sub;
                                } else {
                                    if ((enc & 0x7f200000) == 0x6a000000)
                                        return OP_ands;
                                    if ((enc & 0x7f200000) == 0x6a200000)
                                        return OP_bics;
                                    if ((enc & 0x7f200000) == 0x6b000000)
                                        return OP_subs;
                                }
                            } else {
                                if ((enc >> 27 & 1) == 0) {
                                    if ((enc & 0xff800000) == 0xf2800000)
                                        return OP_movk;
                                    if ((enc & 0xff800000) == 0xd2800000)
                                        return OP_movz;
                                } else {
                                    if ((enc & 0x7fe00c00) == 0x5a800000)
                                        return OP_csinv;
                                    if ((enc & 0x7fe00c00) == 0x5a800400)
                                        return OP_csneg;
                                }
                            }
                        }
                    }
                }
            }
        } else {
            if ((enc >> 30 & 1) == 0) {
                if ((enc >> 23 & 1) == 0) {
                    if ((enc >> 31 & 1) == 0) {
                        if ((enc >> 21 & 1) == 0) {
                            if ((enc >> 25 & 1) == 0) {
                                if ((enc >> 24 & 1) == 0) {
                                    if ((enc >> 28 & 1) == 0) {
                                        if ((enc & 0xffe08000) == 0x08408000)
                                            return OP_ldaxrb;
                                        if ((enc & 0xffc00000) == 0x28400000)
                                            return OP_ldnp;
                                        if ((enc & 0xffe08000) == 0x08400000)
                                            return OP_ldxrb;
                                    } else {
                                        if ((enc >> 10 & 1) == 0) {
                                            if ((enc >> 11 & 1) == 0) {
                                                if ((enc & 0x9f000000) == 0x10000000)
                                                    return OP_adr;
                                                if ((enc & 0xff000000) == 0x18000000)
                                                    return OP_ldr;
                                                if ((enc & 0xffe00c00) == 0x38400000)
                                                    return OP_ldurb;
                                            } else {
                                                if ((enc & 0x9f000000) == 0x10000000)
                                                    return OP_adr;
                                                if ((enc & 0xff000000) == 0x18000000)
                                                    return OP_ldr;
                                                if ((enc & 0xffe00c00) == 0x38400800)
                                                    return OP_ldtrb;
                                            }
                                        } else {
                                            if ((enc >> 11 & 1) == 0) {
                                                if ((enc & 0x9f000000) == 0x10000000)
                                                    return OP_adr;
                                                if ((enc & 0xff000000) == 0x18000000)
                                                    return OP_ldr;
                                                if ((enc & 0xffe00c00) == 0x38400400)
                                                    return OP_ldrb;
                                            } else {
                                                if ((enc & 0x9f000000) == 0x10000000)
                                                    return OP_adr;
                                                if ((enc & 0xff000000) == 0x18000000)
                                                    return OP_ldr;
                                                if ((enc & 0xffe00c00) == 0x38400c00)
                                                    return OP_ldrb;
                                            }
                                        }
                                    }
                                } else {
                                    if ((enc >> 27 & 1) == 0) {
                                        if ((enc & 0x7f800000) == 0x11000000)
                                            return OP_add;
                                        if ((enc & 0x7f800000) == 0x31000000)
                                            return OP_adds;
                                    } else {
                                        if ((enc & 0xffc00000) == 0x29400000)
                                            return OP_ldp;
                                        if ((enc & 0xffc00000) == 0x39400000)
                                            return OP_ldrb;
                                    }
                                }
                            } else {
                                if ((enc >> 28 & 1) == 0) {
                                    if ((enc >> 24 & 1) == 0) {
                                        if ((enc & 0x7f200000) == 0x0a000000)
                                            return OP_and;
                                        if ((enc & 0x7f200000) == 0x2a000000)
                                            return OP_orr;
                                    } else {
                                        if ((enc & 0x7f200000) == 0x0b000000)
                                            return OP_add;
                                        if ((enc & 0x7f200000) == 0x2b000000)
                                            return OP_adds;
                                    }
                                } else {
                                    if ((enc >> 27 & 1) == 0) {
                                        if ((enc & 0x7f800000) == 0x12000000)
                                            return OP_and;
                                        if ((enc & 0x7f800000) == 0x32000000)
                                            return OP_orr;
                                    } else {
                                        if ((enc & 0x7fe00c10) == 0x3a400000)
                                            return OP_ccmn;
                                        if ((enc & 0x7fe00c10) == 0x3a400800)
                                            return OP_ccmn;
                                    }
                                }
                            }
                        } else {
                            if ((enc >> 28 & 1) == 0) {
                                if ((enc >> 29 & 1) == 0) {
                                    if ((enc & 0x7f200000) == 0x0a200000)
                                        return OP_bic;
                                    if ((enc & 0xffe0fc00) == 0x08607c00)
                                        return OP_caspa;
                                    if ((enc & 0xffe0fc00) == 0x0860fc00)
                                        return OP_caspal;
                                } else {
                                    if ((enc & 0xffc00000) == 0x28400000)
                                        return OP_ldnp;
                                    if ((enc & 0xffc00000) == 0x29400000)
                                        return OP_ldp;
                                    if ((enc & 0x7f200000) == 0x2a200000)
                                        return OP_orn;
                                }
                            } else {
                                if ((enc >> 27 & 1) == 0) {
                                    if ((enc >> 24 & 1) == 0) {
                                        if ((enc & 0x9f000000) == 0x10000000)
                                            return OP_adr;
                                        if ((enc & 0x7f800000) == 0x12000000)
                                            return OP_and;
                                        if ((enc & 0x7f800000) == 0x32000000)
                                            return OP_orr;
                                    } else {
                                        if ((enc & 0x7f800000) == 0x11000000)
                                            return OP_add;
                                        if ((enc & 0x7f800000) == 0x31000000)
                                            return OP_adds;
                                    }
                                } else {
                                    if ((enc >> 12 & 1) == 0) {
                                        if ((enc >> 13 & 1) == 0) {
                                            if ((enc >> 11 & 1) == 0) {
                                                if ((enc >> 14 & 1) == 0) {
                                                    if ((enc >> 15 & 1) == 0) {
                                                        if ((enc & 0xffe0fc00) == 0x38600000)
                                                            return OP_ldaddlb;
                                                        if ((enc & 0xff000000) == 0x18000000)
                                                            return OP_ldr;
                                                        if ((enc & 0xffc00000) == 0x39400000)
                                                            return OP_ldrb;
                                                    } else {
                                                        if ((enc & 0xff000000) == 0x18000000)
                                                            return OP_ldr;
                                                        if ((enc & 0xffc00000) == 0x39400000)
                                                            return OP_ldrb;
                                                        if ((enc & 0xffe0fc00) == 0x38608000)
                                                            return OP_swplb;
                                                    }
                                                } else {
                                                    if ((enc & 0xff000000) == 0x18000000)
                                                        return OP_ldr;
                                                    if ((enc & 0xffc00000) == 0x39400000)
                                                        return OP_ldrb;
                                                    if ((enc & 0xffe0fc00) == 0x38604000)
                                                        return OP_ldsmaxlb;
                                                }
                                            } else {
                                                if ((enc & 0xff000000) == 0x18000000)
                                                    return OP_ldr;
                                                if ((enc & 0xffe00c00) == 0x38600800)
                                                    return OP_ldrb;
                                                if ((enc & 0xffc00000) == 0x39400000)
                                                    return OP_ldrb;
                                            }
                                        } else {
                                            if ((enc >> 11 & 1) == 0) {
                                                if ((enc >> 14 & 1) == 0) {
                                                    if ((enc & 0xffe0fc00) == 0x38602000)
                                                        return OP_ldeorlb;
                                                    if ((enc & 0xff000000) == 0x18000000)
                                                        return OP_ldr;
                                                    if ((enc & 0xffc00000) == 0x39400000)
                                                        return OP_ldrb;
                                                } else {
                                                    if ((enc & 0xff000000) == 0x18000000)
                                                        return OP_ldr;
                                                    if ((enc & 0xffc00000) == 0x39400000)
                                                        return OP_ldrb;
                                                    if ((enc & 0xffe0fc00) == 0x38606000)
                                                        return OP_ldumaxlb;
                                                }
                                            } else {
                                                if ((enc & 0xff000000) == 0x18000000)
                                                    return OP_ldr;
                                                if ((enc & 0xffe00c00) == 0x38600800)
                                                    return OP_ldrb;
                                                if ((enc & 0xffc00000) == 0x39400000)
                                                    return OP_ldrb;
                                            }
                                        }
                                    } else {
                                        if ((enc >> 13 & 1) == 0) {
                                            if ((enc >> 11 & 1) == 0) {
                                                if ((enc >> 14 & 1) == 0) {
                                                    if ((enc & 0xffe0fc00) == 0x38601000)
                                                        return OP_ldclrlb;
                                                    if ((enc & 0xff000000) == 0x18000000)
                                                        return OP_ldr;
                                                    if ((enc & 0xffc00000) == 0x39400000)
                                                        return OP_ldrb;
                                                } else {
                                                    if ((enc & 0xff000000) == 0x18000000)
                                                        return OP_ldr;
                                                    if ((enc & 0xffc00000) == 0x39400000)
                                                        return OP_ldrb;
                                                    if ((enc & 0xffe0fc00) == 0x38605000)
                                                        return OP_ldsminlb;
                                                }
                                            } else {
                                                if ((enc & 0xff000000) == 0x18000000)
                                                    return OP_ldr;
                                                if ((enc & 0xffe00c00) == 0x38600800)
                                                    return OP_ldrb;
                                                if ((enc & 0xffc00000) == 0x39400000)
                                                    return OP_ldrb;
                                            }
                                        } else {
                                            if ((enc >> 11 & 1) == 0) {
                                                if ((enc >> 14 & 1) == 0) {
                                                    if ((enc & 0xff000000) == 0x18000000)
                                                        return OP_ldr;
                                                    if ((enc & 0xffc00000) == 0x39400000)
                                                        return OP_ldrb;
                                                    if ((enc & 0xffe0fc00) == 0x38603000)
                                                        return OP_ldsetlb;
                                                } else {
                                                    if ((enc & 0xff000000) == 0x18000000)
                                                        return OP_ldr;
                                                    if ((enc & 0xffc00000) == 0x39400000)
                                                        return OP_ldrb;
                                                    if ((enc & 0xffe0fc00) == 0x38607000)
                                                        return OP_lduminlb;
                                                }
                                            } else {
                                                if ((enc & 0xff000000) == 0x18000000)
                                                    return OP_ldr;
                                                if ((enc & 0xffe00c00) == 0x38600800)
                                                    return OP_ldrb;
                                                if ((enc & 0xffc00000) == 0x39400000)
                                                    return OP_ldrb;
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    } else {
                        if ((enc >> 21 & 1) == 0) {
                            if ((enc >> 25 & 1) == 0) {
                                if ((enc >> 24 & 1) == 0) {
                                    if ((enc >> 28 & 1) == 0) {
                                        if ((enc & 0xffe08000) == 0x88408000)
                                            return OP_ldaxr;
                                        if ((enc & 0xffc00000) == 0xa8400000)
                                            return OP_ldnp;
                                        if ((enc & 0xffe08000) == 0x88400000)
                                            return OP_ldxr;
                                    } else {
                                        if ((enc >> 10 & 1) == 0) {
                                            if ((enc >> 11 & 1) == 0) {
                                                if ((enc & 0x9f000000) == 0x90000000)
                                                    return OP_adrp;
                                                if ((enc & 0xff000000) == 0x98000000)
                                                    return OP_ldrsw;
                                                if ((enc & 0xffe00c00) == 0xb8400000)
                                                    return OP_ldur;
                                            } else {
                                                if ((enc & 0x9f000000) == 0x90000000)
                                                    return OP_adrp;
                                                if ((enc & 0xff000000) == 0x98000000)
                                                    return OP_ldrsw;
                                                if ((enc & 0xffe00c00) == 0xb8400800)
                                                    return OP_ldtr;
                                            }
                                        } else {
                                            if ((enc >> 11 & 1) == 0) {
                                                if ((enc & 0x9f000000) == 0x90000000)
                                                    return OP_adrp;
                                                if ((enc & 0xffe00c00) == 0xb8400400)
                                                    return OP_ldr;
                                                if ((enc & 0xff000000) == 0x98000000)
                                                    return OP_ldrsw;
                                            } else {
                                                if ((enc & 0x9f000000) == 0x90000000)
                                                    return OP_adrp;
                                                if ((enc & 0xffe00c00) == 0xb8400c00)
                                                    return OP_ldr;
                                                if ((enc & 0xff000000) == 0x98000000)
                                                    return OP_ldrsw;
                                            }
                                        }
                                    }
                                } else {
                                    if ((enc >> 27 & 1) == 0) {
                                        if ((enc & 0x7f800000) == 0x11000000)
                                            return OP_add;
                                        if ((enc & 0x7f800000) == 0x31000000)
                                            return OP_adds;
                                    } else {
                                        if ((enc & 0xffc00000) == 0xa9400000)
                                            return OP_ldp;
                                        if ((enc & 0xffc00000) == 0xb9400000)
                                            return OP_ldr;
                                    }
                                }
                            } else {
                                if ((enc >> 24 & 1) == 0) {
                                    if ((enc >> 27 & 1) == 0) {
                                        if ((enc & 0x7f800000) == 0x12000000)
                                            return OP_and;
                                        if ((enc & 0x7f800000) == 0x32000000)
                                            return OP_orr;
                                    } else {
                                        if ((enc >> 28 & 1) == 0) {
                                            if ((enc & 0x7f200000) == 0x0a000000)
                                                return OP_and;
                                            if ((enc & 0x7f200000) == 0x2a000000)
                                                return OP_orr;
                                        } else {
                                            if ((enc & 0x7fe00c10) == 0x3a400000)
                                                return OP_ccmn;
                                            if ((enc & 0x7fe00c10) == 0x3a400800)
                                                return OP_ccmn;
                                        }
                                    }
                                } else {
                                    if ((enc >> 27 & 1) == 0) {
                                        if ((enc & 0xffc00000) == 0xb3400000)
                                            return OP_bfm;
                                        if ((enc & 0xffc00000) == 0x93400000)
                                            return OP_sbfm;
                                    } else {
                                        if ((enc & 0x7f200000) == 0x0b000000)
                                            return OP_add;
                                        if ((enc & 0x7f200000) == 0x2b000000)
                                            return OP_adds;
                                        if ((enc & 0xffe08000) == 0x9b400000)
                                            return OP_smulh;
                                    }
                                }
                            }
                        } else {
                            if ((enc >> 27 & 1) == 0) {
                                if ((enc >> 24 & 1) == 0) {
                                    if ((enc & 0x9f000000) == 0x90000000)
                                        return OP_adrp;
                                    if ((enc & 0x7f800000) == 0x12000000)
                                        return OP_and;
                                    if ((enc & 0x7f800000) == 0x32000000)
                                        return OP_orr;
                                } else {
                                    if ((enc >> 25 & 1) == 0) {
                                        if ((enc & 0x7f800000) == 0x11000000)
                                            return OP_add;
                                        if ((enc & 0x7f800000) == 0x31000000)
                                            return OP_adds;
                                    } else {
                                        if ((enc & 0xffc00000) == 0xb3400000)
                                            return OP_bfm;
                                        if ((enc & 0xffc00000) == 0x93400000)
                                            return OP_sbfm;
                                    }
                                }
                            } else {
                                if ((enc >> 28 & 1) == 0) {
                                    if ((enc >> 29 & 1) == 0) {
                                        if ((enc & 0x7f200000) == 0x0a200000)
                                            return OP_bic;
                                        if ((enc & 0xffe08000) == 0x88608000)
                                            return OP_ldaxp;
                                        if ((enc & 0xffe08000) == 0x88600000)
                                            return OP_ldxp;
                                    } else {
                                        if ((enc & 0xffc00000) == 0xa8400000)
                                            return OP_ldnp;
                                        if ((enc & 0xffc00000) == 0xa9400000)
                                            return OP_ldp;
                                        if ((enc & 0x7f200000) == 0x2a200000)
                                            return OP_orn;
                                    }
                                } else {
                                    if ((enc >> 12 & 1) == 0) {
                                        if ((enc >> 13 & 1) == 0) {
                                            if ((enc >> 11 & 1) == 0) {
                                                if ((enc >> 14 & 1) == 0) {
                                                    if ((enc >> 15 & 1) == 0) {
                                                        if ((enc & 0xffe0fc00) == 0xb8600000)
                                                            return OP_ldaddl;
                                                        if ((enc & 0xffc00000) == 0xb9400000)
                                                            return OP_ldr;
                                                        if ((enc & 0xff000000) == 0x98000000)
                                                            return OP_ldrsw;
                                                    } else {
                                                        if ((enc & 0xffc00000) == 0xb9400000)
                                                            return OP_ldr;
                                                        if ((enc & 0xff000000) == 0x98000000)
                                                            return OP_ldrsw;
                                                        if ((enc & 0xffe0fc00) == 0xb8608000)
                                                            return OP_swpl;
                                                    }
                                                } else {
                                                    if ((enc & 0xffc00000) == 0xb9400000)
                                                        return OP_ldr;
                                                    if ((enc & 0xff000000) == 0x98000000)
                                                        return OP_ldrsw;
                                                    if ((enc & 0xffe0fc00) == 0xb8604000)
                                                        return OP_ldsmaxl;
                                                }
                                            } else {
                                                if ((enc & 0xffe00c00) == 0xb8600800)
                                                    return OP_ldr;
                                                if ((enc & 0xffc00000) == 0xb9400000)
                                                    return OP_ldr;
                                                if ((enc & 0xff000000) == 0x98000000)
                                                    return OP_ldrsw;
                                            }
                                        } else {
                                            if ((enc >> 11 & 1) == 0) {
                                                if ((enc >> 14 & 1) == 0) {
                                                    if ((enc & 0xffe0fc00) == 0xb8602000)
                                                        return OP_ldeorl;
                                                    if ((enc & 0xffc00000) == 0xb9400000)
                                                        return OP_ldr;
                                                    if ((enc & 0xff000000) == 0x98000000)
                                                        return OP_ldrsw;
                                                } else {
                                                    if ((enc & 0xffc00000) == 0xb9400000)
                                                        return OP_ldr;
                                                    if ((enc & 0xff000000) == 0x98000000)
                                                        return OP_ldrsw;
                                                    if ((enc & 0xffe0fc00) == 0xb8606000)
                                                        return OP_ldumaxl;
                                                }
                                            } else {
                                                if ((enc & 0xffe00c00) == 0xb8600800)
                                                    return OP_ldr;
                                                if ((enc & 0xffc00000) == 0xb9400000)
                                                    return OP_ldr;
                                                if ((enc & 0xff000000) == 0x98000000)
                                                    return OP_ldrsw;
                                            }
                                        }
                                    } else {
                                        if ((enc >> 13 & 1) == 0) {
                                            if ((enc >> 11 & 1) == 0) {
                                                if ((enc >> 14 & 1) == 0) {
                                                    if ((enc & 0xffe0fc00) == 0xb8601000)
                                                        return OP_ldclrl;
                                                    if ((enc & 0xffc00000) == 0xb9400000)
                                                        return OP_ldr;
                                                    if ((enc & 0xff000000) == 0x98000000)
                                                        return OP_ldrsw;
                                                } else {
                                                    if ((enc & 0xffc00000) == 0xb9400000)
                                                        return OP_ldr;
                                                    if ((enc & 0xff000000) == 0x98000000)
                                                        return OP_ldrsw;
                                                    if ((enc & 0xffe0fc00) == 0xb8605000)
                                                        return OP_ldsminl;
                                                }
                                            } else {
                                                if ((enc & 0xffe00c00) == 0xb8600800)
                                                    return OP_ldr;
                                                if ((enc & 0xffc00000) == 0xb9400000)
                                                    return OP_ldr;
                                                if ((enc & 0xff000000) == 0x98000000)
                                                    return OP_ldrsw;
                                            }
                                        } else {
                                            if ((enc >> 11 & 1) == 0) {
                                                if ((enc >> 14 & 1) == 0) {
                                                    if ((enc & 0xffc00000) == 0xb9400000)
                                                        return OP_ldr;
                                                    if ((enc & 0xff000000) == 0x98000000)
                                                        return OP_ldrsw;
                                                    if ((enc & 0xffe0fc00) == 0xb8603000)
                                                        return OP_ldsetl;
                                                } else {
                                                    if ((enc & 0xffc00000) == 0xb9400000)
                                                        return OP_ldr;
                                                    if ((enc & 0xff000000) == 0x98000000)
                                                        return OP_ldrsw;
                                                    if ((enc & 0xffe0fc00) == 0xb8607000)
                                                        return OP_lduminl;
                                                }
                                            } else {
                                                if ((enc & 0xffe00c00) == 0xb8600800)
                                                    return OP_ldr;
                                                if ((enc & 0xffc00000) == 0xb9400000)
                                                    return OP_ldr;
                                                if ((enc & 0xff000000) == 0x98000000)
                                                    return OP_ldrsw;
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                } else {
                    if ((enc >> 29 & 1) == 0) {
                        if ((enc >> 12 & 1) == 0) {
                            if ((enc >> 31 & 1) == 0) {
                                if ((enc >> 10 & 1) == 0) {
                                    if ((enc >> 28 & 1) == 0) {
                                        if ((enc & 0x7f200000) == 0x0b000000)
                                            return OP_add;
                                        if ((enc & 0x7f200000) == 0x0a000000)
                                            return OP_and;
                                        if ((enc & 0x7f200000) == 0x0a200000)
                                            return OP_bic;
                                    } else {
                                        if ((enc >> 11 & 1) == 0) {
                                            if ((enc >> 25 & 1) == 0) {
                                                if ((enc & 0x9f000000) == 0x10000000)
                                                    return OP_adr;
                                                if ((enc & 0xff000000) == 0x18000000)
                                                    return OP_ldr;
                                            } else {
                                                if ((enc & 0xffe0fc00) == 0x1ac04000)
                                                    return OP_crc32b;
                                                if ((enc & 0x7fe0fc00) == 0x1ac02000)
                                                    return OP_lslv;
                                                if ((enc & 0xff800000) == 0x12800000)
                                                    return OP_movn;
                                            }
                                        } else {
                                            if ((enc >> 25 & 1) == 0) {
                                                if ((enc & 0x9f000000) == 0x10000000)
                                                    return OP_adr;
                                                if ((enc & 0xff000000) == 0x18000000)
                                                    return OP_ldr;
                                            } else {
                                                if ((enc >> 13 & 1) == 0) {
                                                    if ((enc & 0xffe0fc00) == 0x1ac04800)
                                                        return OP_crc32w;
                                                    if ((enc & 0xff800000) == 0x12800000)
                                                        return OP_movn;
                                                    if ((enc & 0x7fe0fc00) == 0x1ac00800)
                                                        return OP_udiv;
                                                } else {
                                                    if ((enc & 0x7fe0fc00) == 0x1ac02800)
                                                        return OP_asrv;
                                                    if ((enc & 0xff800000) == 0x12800000)
                                                        return OP_movn;
                                                }
                                            }
                                        }
                                    }
                                } else {
                                    if ((enc >> 28 & 1) == 0) {
                                        if ((enc & 0x7f200000) == 0x0b000000)
                                            return OP_add;
                                        if ((enc & 0x7f200000) == 0x0a000000)
                                            return OP_and;
                                        if ((enc & 0x7f200000) == 0x0a200000)
                                            return OP_bic;
                                    } else {
                                        if ((enc >> 11 & 1) == 0) {
                                            if ((enc >> 25 & 1) == 0) {
                                                if ((enc & 0x9f000000) == 0x10000000)
                                                    return OP_adr;
                                                if ((enc & 0xff000000) == 0x18000000)
                                                    return OP_ldr;
                                            } else {
                                                if ((enc & 0xffe0fc00) == 0x1ac04400)
                                                    return OP_crc32h;
                                                if ((enc & 0x7fe0fc00) == 0x1ac02400)
                                                    return OP_lsrv;
                                                if ((enc & 0xff800000) == 0x12800000)
                                                    return OP_movn;
                                            }
                                        } else {
                                            if ((enc >> 25 & 1) == 0) {
                                                if ((enc & 0x9f000000) == 0x10000000)
                                                    return OP_adr;
                                                if ((enc & 0xff000000) == 0x18000000)
                                                    return OP_ldr;
                                            } else {
                                                if ((enc & 0xff800000) == 0x12800000)
                                                    return OP_movn;
                                                if ((enc & 0x7fe0fc00) == 0x1ac02c00)
                                                    return OP_rorv;
                                                if ((enc & 0x7fe0fc00) == 0x1ac00c00)
                                                    return OP_sdiv;
                                            }
                                        }
                                    }
                                }
                            } else {
                                if ((enc >> 10 & 1) == 0) {
                                    if ((enc >> 24 & 1) == 0) {
                                        if ((enc >> 25 & 1) == 0) {
                                            if ((enc & 0x9f000000) == 0x90000000)
                                                return OP_adrp;
                                            if ((enc & 0xff000000) == 0x98000000)
                                                return OP_ldrsw;
                                        } else {
                                            if ((enc >> 28 & 1) == 0) {
                                                if ((enc & 0x7f200000) == 0x0a000000)
                                                    return OP_and;
                                                if ((enc & 0x7f200000) == 0x0a200000)
                                                    return OP_bic;
                                            } else {
                                                if ((enc >> 11 & 1) == 0) {
                                                    if ((enc & 0x7fe0fc00) == 0x1ac02000)
                                                        return OP_lslv;
                                                    if ((enc & 0xff800000) == 0x92800000)
                                                        return OP_movn;
                                                } else {
                                                    if ((enc & 0x7fe0fc00) == 0x1ac02800)
                                                        return OP_asrv;
                                                    if ((enc & 0xff800000) == 0x92800000)
                                                        return OP_movn;
                                                    if ((enc & 0x7fe0fc00) == 0x1ac00800)
                                                        return OP_udiv;
                                                }
                                            }
                                        }
                                    } else {
                                        if ((enc & 0x7f200000) == 0x0b000000)
                                            return OP_add;
                                        if ((enc & 0xffe00000) == 0x93c00000)
                                            return OP_extr;
                                        if ((enc & 0xffe08000) == 0x9bc00000)
                                            return OP_umulh;
                                    }
                                } else {
                                    if ((enc >> 24 & 1) == 0) {
                                        if ((enc >> 13 & 1) == 0) {
                                            if ((enc >> 25 & 1) == 0) {
                                                if ((enc & 0x9f000000) == 0x90000000)
                                                    return OP_adrp;
                                                if ((enc & 0xff000000) == 0x98000000)
                                                    return OP_ldrsw;
                                            } else {
                                                if ((enc >> 28 & 1) == 0) {
                                                    if ((enc & 0x7f200000) == 0x0a000000)
                                                        return OP_and;
                                                    if ((enc & 0x7f200000) == 0x0a200000)
                                                        return OP_bic;
                                                } else {
                                                    if ((enc & 0xffe0fc00) == 0x9ac04c00)
                                                        return OP_crc32x;
                                                    if ((enc & 0xff800000) == 0x92800000)
                                                        return OP_movn;
                                                    if ((enc & 0x7fe0fc00) == 0x1ac00c00)
                                                        return OP_sdiv;
                                                }
                                            }
                                        } else {
                                            if ((enc >> 25 & 1) == 0) {
                                                if ((enc & 0x9f000000) == 0x90000000)
                                                    return OP_adrp;
                                                if ((enc & 0xff000000) == 0x98000000)
                                                    return OP_ldrsw;
                                            } else {
                                                if ((enc >> 28 & 1) == 0) {
                                                    if ((enc & 0x7f200000) == 0x0a000000)
                                                        return OP_and;
                                                    if ((enc & 0x7f200000) == 0x0a200000)
                                                        return OP_bic;
                                                } else {
                                                    if ((enc & 0x7fe0fc00) == 0x1ac02400)
                                                        return OP_lsrv;
                                                    if ((enc & 0xff800000) == 0x92800000)
                                                        return OP_movn;
                                                    if ((enc & 0x7fe0fc00) == 0x1ac02c00)
                                                        return OP_rorv;
                                                }
                                            }
                                        }
                                    } else {
                                        if ((enc & 0x7f200000) == 0x0b000000)
                                            return OP_add;
                                        if ((enc & 0xffe00000) == 0x93c00000)
                                            return OP_extr;
                                        if ((enc & 0xffe08000) == 0x9bc00000)
                                            return OP_umulh;
                                    }
                                }
                            }
                        } else {
                            if ((enc >> 25 & 1) == 0) {
                                if ((enc >> 31 & 1) == 0) {
                                    if ((enc >> 28 & 1) == 0) {
                                        if ((enc & 0xffe0fc00) == 0x08e07c00)
                                            return OP_casab;
                                        if ((enc & 0xffe0fc00) == 0x08e0fc00)
                                            return OP_casalb;
                                        if ((enc & 0xfffffc00) == 0x08dffc00)
                                            return OP_ldarb;
                                    } else {
                                        if ((enc & 0x9f000000) == 0x10000000)
                                            return OP_adr;
                                        if ((enc & 0xff000000) == 0x18000000)
                                            return OP_ldr;
                                    }
                                } else {
                                    if ((enc >> 28 & 1) == 0) {
                                        if ((enc & 0xffe0fc00) == 0x88e07c00)
                                            return OP_casa;
                                        if ((enc & 0xffe0fc00) == 0x88e0fc00)
                                            return OP_casal;
                                        if ((enc & 0xfffffc00) == 0x88dffc00)
                                            return OP_ldar;
                                    } else {
                                        if ((enc & 0x9f000000) == 0x90000000)
                                            return OP_adrp;
                                        if ((enc & 0xff000000) == 0x98000000)
                                            return OP_ldrsw;
                                    }
                                }
                            } else {
                                if ((enc >> 31 & 1) == 0) {
                                    if ((enc >> 28 & 1) == 0) {
                                        if ((enc & 0x7f200000) == 0x0b000000)
                                            return OP_add;
                                        if ((enc & 0x7f200000) == 0x0a000000)
                                            return OP_and;
                                        if ((enc & 0x7f200000) == 0x0a200000)
                                            return OP_bic;
                                    } else {
                                        if ((enc >> 10 & 1) == 0) {
                                            if ((enc & 0xffe0fc00) == 0x1ac05000)
                                                return OP_crc32cb;
                                            if ((enc & 0xffe0fc00) == 0x1ac05800)
                                                return OP_crc32cw;
                                            if ((enc & 0xff800000) == 0x12800000)
                                                return OP_movn;
                                        } else {
                                            if ((enc & 0xffe0fc00) == 0x1ac05400)
                                                return OP_crc32ch;
                                            if ((enc & 0xff800000) == 0x12800000)
                                                return OP_movn;
                                        }
                                    }
                                } else {
                                    if ((enc >> 24 & 1) == 0) {
                                        if ((enc >> 28 & 1) == 0) {
                                            if ((enc & 0x7f200000) == 0x0a000000)
                                                return OP_and;
                                            if ((enc & 0x7f200000) == 0x0a200000)
                                                return OP_bic;
                                        } else {
                                            if ((enc & 0xffe0fc00) == 0x9ac05c00)
                                                return OP_crc32cx;
                                            if ((enc & 0xff800000) == 0x92800000)
                                                return OP_movn;
                                        }
                                    } else {
                                        if ((enc & 0x7f200000) == 0x0b000000)
                                            return OP_add;
                                        if ((enc & 0xffe00000) == 0x93c00000)
                                            return OP_extr;
                                        if ((enc & 0xffe08000) == 0x9bc00000)
                                            return OP_umulh;
                                    }
                                }
                            }
                        }
                    } else {
                        if ((enc >> 31 & 1) == 0) {
                            if ((enc >> 21 & 1) == 0) {
                                if ((enc >> 28 & 1) == 0) {
                                    if ((enc >> 24 & 1) == 0) {
                                        if ((enc & 0xffc00000) == 0x28c00000)
                                            return OP_ldp;
                                        if ((enc & 0x7f200000) == 0x2a000000)
                                            return OP_orr;
                                    } else {
                                        if ((enc & 0x7f200000) == 0x2b000000)
                                            return OP_adds;
                                        if ((enc & 0xffc00000) == 0x29c00000)
                                            return OP_ldp;
                                    }
                                } else {
                                    if ((enc >> 10 & 1) == 0) {
                                        if ((enc >> 11 & 1) == 0) {
                                            if ((enc & 0x9f000000) == 0x10000000)
                                                return OP_adr;
                                            if ((enc & 0xffc00000) == 0x39c00000)
                                                return OP_ldrsb;
                                            if ((enc & 0xffe00c00) == 0x38c00000)
                                                return OP_ldursb;
                                        } else {
                                            if ((enc & 0x9f000000) == 0x10000000)
                                                return OP_adr;
                                            if ((enc & 0xffc00000) == 0x39c00000)
                                                return OP_ldrsb;
                                            if ((enc & 0xffe00c00) == 0x38c00800)
                                                return OP_ldtrsb;
                                        }
                                    } else {
                                        if ((enc >> 11 & 1) == 0) {
                                            if ((enc & 0x9f000000) == 0x10000000)
                                                return OP_adr;
                                            if ((enc & 0xffe00c00) == 0x38c00400)
                                                return OP_ldrsb;
                                            if ((enc & 0xffc00000) == 0x39c00000)
                                                return OP_ldrsb;
                                        } else {
                                            if ((enc & 0x9f000000) == 0x10000000)
                                                return OP_adr;
                                            if ((enc & 0xffe00c00) == 0x38c00c00)
                                                return OP_ldrsb;
                                            if ((enc & 0xffc00000) == 0x39c00000)
                                                return OP_ldrsb;
                                        }
                                    }
                                }
                            } else {
                                if ((enc >> 12 & 1) == 0) {
                                    if ((enc >> 28 & 1) == 0) {
                                        if ((enc & 0xffc00000) == 0x28c00000)
                                            return OP_ldp;
                                        if ((enc & 0xffc00000) == 0x29c00000)
                                            return OP_ldp;
                                        if ((enc & 0x7f200000) == 0x2a200000)
                                            return OP_orn;
                                    } else {
                                        if ((enc >> 13 & 1) == 0) {
                                            if ((enc >> 11 & 1) == 0) {
                                                if ((enc >> 14 & 1) == 0) {
                                                    if ((enc >> 15 & 1) == 0) {
                                                        if ((enc & 0x9f000000) == 0x10000000)
                                                            return OP_adr;
                                                        if ((enc & 0xffe0fc00) == 0x38e00000)
                                                            return OP_ldaddalb;
                                                        if ((enc & 0xffc00000) == 0x39c00000)
                                                            return OP_ldrsb;
                                                    } else {
                                                        if ((enc & 0x9f000000) == 0x10000000)
                                                            return OP_adr;
                                                        if ((enc & 0xffc00000) == 0x39c00000)
                                                            return OP_ldrsb;
                                                        if ((enc & 0xffe0fc00) == 0x38e08000)
                                                            return OP_swpalb;
                                                    }
                                                } else {
                                                    if ((enc & 0x9f000000) == 0x10000000)
                                                        return OP_adr;
                                                    if ((enc & 0xffc00000) == 0x39c00000)
                                                        return OP_ldrsb;
                                                    if ((enc & 0xffe0fc00) == 0x38e04000)
                                                        return OP_ldsmaxalb;
                                                }
                                            } else {
                                                if ((enc & 0x9f000000) == 0x10000000)
                                                    return OP_adr;
                                                if ((enc & 0xffe00c00) == 0x38e00800)
                                                    return OP_ldrsb;
                                                if ((enc & 0xffc00000) == 0x39c00000)
                                                    return OP_ldrsb;
                                            }
                                        } else {
                                            if ((enc >> 11 & 1) == 0) {
                                                if ((enc >> 14 & 1) == 0) {
                                                    if ((enc & 0x9f000000) == 0x10000000)
                                                        return OP_adr;
                                                    if ((enc & 0xffe0fc00) == 0x38e02000)
                                                        return OP_ldeoralb;
                                                    if ((enc & 0xffc00000) == 0x39c00000)
                                                        return OP_ldrsb;
                                                } else {
                                                    if ((enc & 0x9f000000) == 0x10000000)
                                                        return OP_adr;
                                                    if ((enc & 0xffc00000) == 0x39c00000)
                                                        return OP_ldrsb;
                                                    if ((enc & 0xffe0fc00) == 0x38e06000)
                                                        return OP_ldumaxalb;
                                                }
                                            } else {
                                                if ((enc & 0x9f000000) == 0x10000000)
                                                    return OP_adr;
                                                if ((enc & 0xffe00c00) == 0x38e00800)
                                                    return OP_ldrsb;
                                                if ((enc & 0xffc00000) == 0x39c00000)
                                                    return OP_ldrsb;
                                            }
                                        }
                                    }
                                } else {
                                    if ((enc >> 28 & 1) == 0) {
                                        if ((enc & 0xffc00000) == 0x28c00000)
                                            return OP_ldp;
                                        if ((enc & 0xffc00000) == 0x29c00000)
                                            return OP_ldp;
                                        if ((enc & 0x7f200000) == 0x2a200000)
                                            return OP_orn;
                                    } else {
                                        if ((enc >> 13 & 1) == 0) {
                                            if ((enc >> 11 & 1) == 0) {
                                                if ((enc >> 14 & 1) == 0) {
                                                    if ((enc & 0x9f000000) == 0x10000000)
                                                        return OP_adr;
                                                    if ((enc & 0xffe0fc00) == 0x38e01000)
                                                        return OP_ldclralb;
                                                    if ((enc & 0xffc00000) == 0x39c00000)
                                                        return OP_ldrsb;
                                                } else {
                                                    if ((enc & 0x9f000000) == 0x10000000)
                                                        return OP_adr;
                                                    if ((enc & 0xffc00000) == 0x39c00000)
                                                        return OP_ldrsb;
                                                    if ((enc & 0xffe0fc00) == 0x38e05000)
                                                        return OP_ldsminalb;
                                                }
                                            } else {
                                                if ((enc & 0x9f000000) == 0x10000000)
                                                    return OP_adr;
                                                if ((enc & 0xffe00c00) == 0x38e00800)
                                                    return OP_ldrsb;
                                                if ((enc & 0xffc00000) == 0x39c00000)
                                                    return OP_ldrsb;
                                            }
                                        } else {
                                            if ((enc >> 11 & 1) == 0) {
                                                if ((enc >> 14 & 1) == 0) {
                                                    if ((enc & 0x9f000000) == 0x10000000)
                                                        return OP_adr;
                                                    if ((enc & 0xffc00000) == 0x39c00000)
                                                        return OP_ldrsb;
                                                    if ((enc & 0xffe0fc00) == 0x38e03000)
                                                        return OP_ldsetalb;
                                                } else {
                                                    if ((enc & 0x9f000000) == 0x10000000)
                                                        return OP_adr;
                                                    if ((enc & 0xffc00000) == 0x39c00000)
                                                        return OP_ldrsb;
                                                    if ((enc & 0xffe0fc00) == 0x38e07000)
                                                        return OP_lduminalb;
                                                }
                                            } else {
                                                if ((enc & 0x9f000000) == 0x10000000)
                                                    return OP_adr;
                                                if ((enc & 0xffe00c00) == 0x38e00800)
                                                    return OP_ldrsb;
                                                if ((enc & 0xffc00000) == 0x39c00000)
                                                    return OP_ldrsb;
                                            }
                                        }
                                    }
                                }
                            }
                        } else {
                            if ((enc >> 28 & 1) == 0) {
                                if ((enc >> 24 & 1) == 0) {
                                    if ((enc & 0xffc00000) == 0xa8c00000)
                                        return OP_ldp;
                                    if ((enc & 0x7f200000) == 0x2a200000)
                                        return OP_orn;
                                    if ((enc & 0x7f200000) == 0x2a000000)
                                        return OP_orr;
                                } else {
                                    if ((enc & 0x7f200000) == 0x2b000000)
                                        return OP_adds;
                                    if ((enc & 0xffc00000) == 0xa9c00000)
                                        return OP_ldp;
                                }
                            } else {
                                if ((enc >> 12 & 1) == 0) {
                                    if ((enc >> 13 & 1) == 0) {
                                        if ((enc >> 14 & 1) == 0) {
                                            if ((enc & 0x9f000000) == 0x90000000)
                                                return OP_adrp;
                                            if ((enc & 0xffe0fc00) == 0xb8e00000)
                                                return OP_ldaddal;
                                            if ((enc & 0xffe0fc00) == 0xb8e08000)
                                                return OP_swpal;
                                        } else {
                                            if ((enc & 0x9f000000) == 0x90000000)
                                                return OP_adrp;
                                            if ((enc & 0xffe0fc00) == 0xb8e04000)
                                                return OP_ldsmaxal;
                                        }
                                    } else {
                                        if ((enc & 0x9f000000) == 0x90000000)
                                            return OP_adrp;
                                        if ((enc & 0xffe0fc00) == 0xb8e02000)
                                            return OP_ldeoral;
                                        if ((enc & 0xffe0fc00) == 0xb8e06000)
                                            return OP_ldumaxal;
                                    }
                                } else {
                                    if ((enc >> 13 & 1) == 0) {
                                        if ((enc & 0x9f000000) == 0x90000000)
                                            return OP_adrp;
                                        if ((enc & 0xffe0fc00) == 0xb8e01000)
                                            return OP_ldclral;
                                        if ((enc & 0xffe0fc00) == 0xb8e05000)
                                            return OP_ldsminal;
                                    } else {
                                        if ((enc & 0x9f000000) == 0x90000000)
                                            return OP_adrp;
                                        if ((enc & 0xffe0fc00) == 0xb8e03000)
                                            return OP_ldsetal;
                                        if ((enc & 0xffe0fc00) == 0xb8e07000)
                                            return OP_lduminal;
                                    }
                                }
                            }
                        }
                    }
                }
            } else {
                if ((enc >> 23 & 1) == 0) {
                    if ((enc >> 31 & 1) == 0) {
                        if ((enc >> 21 & 1) == 0) {
                            if ((enc >> 25 & 1) == 0) {
                                if ((enc >> 24 & 1) == 0) {
                                    if ((enc >> 29 & 1) == 0) {
                                        if ((enc >> 28 & 1) == 0) {
                                            if ((enc & 0xffe08000) == 0x48408000)
                                                return OP_ldaxrh;
                                            if ((enc & 0xffe08000) == 0x48400000)
                                                return OP_ldxrh;
                                        } else {
                                            if ((enc & 0x9f000000) == 0x10000000)
                                                return OP_adr;
                                            if ((enc & 0xff000000) == 0x58000000)
                                                return OP_ldr;
                                        }
                                    } else {
                                        if ((enc >> 10 & 1) == 0) {
                                            if ((enc & 0x9f000000) == 0x10000000)
                                                return OP_adr;
                                            if ((enc & 0xffe00c00) == 0x78400800)
                                                return OP_ldtrh;
                                            if ((enc & 0xffe00c00) == 0x78400000)
                                                return OP_ldurh;
                                        } else {
                                            if ((enc & 0x9f000000) == 0x10000000)
                                                return OP_adr;
                                            if ((enc & 0xffe00c00) == 0x78400400)
                                                return OP_ldrh;
                                            if ((enc & 0xffe00c00) == 0x78400c00)
                                                return OP_ldrh;
                                        }
                                    }
                                } else {
                                    if ((enc >> 27 & 1) == 0) {
                                        if ((enc & 0x7f800000) == 0x51000000)
                                            return OP_sub;
                                        if ((enc & 0x7f800000) == 0x71000000)
                                            return OP_subs;
                                    } else {
                                        if ((enc & 0xffc00000) == 0x69400000)
                                            return OP_ldpsw;
                                        if ((enc & 0xffc00000) == 0x79400000)
                                            return OP_ldrh;
                                    }
                                }
                            } else {
                                if ((enc >> 28 & 1) == 0) {
                                    if ((enc >> 24 & 1) == 0) {
                                        if ((enc & 0x7f200000) == 0x6a000000)
                                            return OP_ands;
                                        if ((enc & 0x7f200000) == 0x4a000000)
                                            return OP_eor;
                                    } else {
                                        if ((enc & 0x7f200000) == 0x4b000000)
                                            return OP_sub;
                                        if ((enc & 0x7f200000) == 0x6b000000)
                                            return OP_subs;
                                    }
                                } else {
                                    if ((enc >> 27 & 1) == 0) {
                                        if ((enc & 0x7f800000) == 0x72000000)
                                            return OP_ands;
                                        if ((enc & 0x7f800000) == 0x52000000)
                                            return OP_eor;
                                    } else {
                                        if ((enc & 0x7fe00c10) == 0x7a400000)
                                            return OP_ccmp;
                                        if ((enc & 0x7fe00c10) == 0x7a400800)
                                            return OP_ccmp;
                                    }
                                }
                            }
                        } else {
                            if ((enc >> 29 & 1) == 0) {
                                if ((enc >> 27 & 1) == 0) {
                                    if ((enc & 0x9f000000) == 0x10000000)
                                        return OP_adr;
                                    if ((enc & 0x7f800000) == 0x52000000)
                                        return OP_eor;
                                    if ((enc & 0x7f800000) == 0x51000000)
                                        return OP_sub;
                                } else {
                                    if ((enc >> 15 & 1) == 0) {
                                        if ((enc & 0xffe0fc00) == 0x48607c00)
                                            return OP_caspa;
                                        if ((enc & 0x7f200000) == 0x4a200000)
                                            return OP_eon;
                                        if ((enc & 0xff000000) == 0x58000000)
                                            return OP_ldr;
                                    } else {
                                        if ((enc & 0xffe0fc00) == 0x4860fc00)
                                            return OP_caspal;
                                        if ((enc & 0x7f200000) == 0x4a200000)
                                            return OP_eon;
                                        if ((enc & 0xff000000) == 0x58000000)
                                            return OP_ldr;
                                    }
                                }
                            } else {
                                if ((enc >> 12 & 1) == 0) {
                                    if ((enc >> 24 & 1) == 0) {
                                        if ((enc >> 13 & 1) == 0) {
                                            if ((enc >> 25 & 1) == 0) {
                                                if ((enc >> 11 & 1) == 0) {
                                                    if ((enc >> 14 & 1) == 0) {
                                                        if ((enc & 0x9f000000) == 0x10000000)
                                                            return OP_adr;
                                                        if ((enc & 0xffe0fc00) == 0x78600000)
                                                            return OP_ldaddlh;
                                                        if ((enc & 0xffe0fc00) == 0x78608000)
                                                            return OP_swplh;
                                                    } else {
                                                        if ((enc & 0x9f000000) == 0x10000000)
                                                            return OP_adr;
                                                        if ((enc & 0xffe0fc00) == 0x78604000)
                                                            return OP_ldsmaxlh;
                                                    }
                                                } else {
                                                    if ((enc & 0x9f000000) == 0x10000000)
                                                        return OP_adr;
                                                    if ((enc & 0xffe00c00) == 0x78600800)
                                                        return OP_ldrh;
                                                }
                                            } else {
                                                if ((enc & 0x7f800000) == 0x72000000)
                                                    return OP_ands;
                                                if ((enc & 0x7f200000) == 0x6a200000)
                                                    return OP_bics;
                                            }
                                        } else {
                                            if ((enc >> 25 & 1) == 0) {
                                                if ((enc >> 11 & 1) == 0) {
                                                    if ((enc & 0x9f000000) == 0x10000000)
                                                        return OP_adr;
                                                    if ((enc & 0xffe0fc00) == 0x78602000)
                                                        return OP_ldeorlh;
                                                    if ((enc & 0xffe0fc00) == 0x78606000)
                                                        return OP_ldumaxlh;
                                                } else {
                                                    if ((enc & 0x9f000000) == 0x10000000)
                                                        return OP_adr;
                                                    if ((enc & 0xffe00c00) == 0x78600800)
                                                        return OP_ldrh;
                                                }
                                            } else {
                                                if ((enc & 0x7f800000) == 0x72000000)
                                                    return OP_ands;
                                                if ((enc & 0x7f200000) == 0x6a200000)
                                                    return OP_bics;
                                            }
                                        }
                                    } else {
                                        if ((enc & 0xffc00000) == 0x69400000)
                                            return OP_ldpsw;
                                        if ((enc & 0xffc00000) == 0x79400000)
                                            return OP_ldrh;
                                        if ((enc & 0x7f800000) == 0x71000000)
                                            return OP_subs;
                                    }
                                } else {
                                    if ((enc >> 24 & 1) == 0) {
                                        if ((enc >> 13 & 1) == 0) {
                                            if ((enc >> 25 & 1) == 0) {
                                                if ((enc >> 11 & 1) == 0) {
                                                    if ((enc & 0x9f000000) == 0x10000000)
                                                        return OP_adr;
                                                    if ((enc & 0xffe0fc00) == 0x78601000)
                                                        return OP_ldclrlh;
                                                    if ((enc & 0xffe0fc00) == 0x78605000)
                                                        return OP_ldsminlh;
                                                } else {
                                                    if ((enc & 0x9f000000) == 0x10000000)
                                                        return OP_adr;
                                                    if ((enc & 0xffe00c00) == 0x78600800)
                                                        return OP_ldrh;
                                                }
                                            } else {
                                                if ((enc & 0x7f800000) == 0x72000000)
                                                    return OP_ands;
                                                if ((enc & 0x7f200000) == 0x6a200000)
                                                    return OP_bics;
                                            }
                                        } else {
                                            if ((enc >> 25 & 1) == 0) {
                                                if ((enc >> 11 & 1) == 0) {
                                                    if ((enc & 0x9f000000) == 0x10000000)
                                                        return OP_adr;
                                                    if ((enc & 0xffe0fc00) == 0x78603000)
                                                        return OP_ldsetlh;
                                                    if ((enc & 0xffe0fc00) == 0x78607000)
                                                        return OP_lduminlh;
                                                } else {
                                                    if ((enc & 0x9f000000) == 0x10000000)
                                                        return OP_adr;
                                                    if ((enc & 0xffe00c00) == 0x78600800)
                                                        return OP_ldrh;
                                                }
                                            } else {
                                                if ((enc & 0x7f800000) == 0x72000000)
                                                    return OP_ands;
                                                if ((enc & 0x7f200000) == 0x6a200000)
                                                    return OP_bics;
                                            }
                                        }
                                    } else {
                                        if ((enc & 0xffc00000) == 0x69400000)
                                            return OP_ldpsw;
                                        if ((enc & 0xffc00000) == 0x79400000)
                                            return OP_ldrh;
                                        if ((enc & 0x7f800000) == 0x71000000)
                                            return OP_subs;
                                    }
                                }
                            }
                        }
                    } else {
                        if ((enc >> 21 & 1) == 0) {
                            if ((enc >> 25 & 1) == 0) {
                                if ((enc >> 29 & 1) == 0) {
                                    if ((enc >> 27 & 1) == 0) {
                                        if ((enc & 0x9f000000) == 0x90000000)
                                            return OP_adrp;
                                        if ((enc & 0x7f800000) == 0x51000000)
                                            return OP_sub;
                                    } else {
                                        if ((enc & 0xffe08000) == 0xc8408000)
                                            return OP_ldaxr;
                                        if ((enc & 0xffe08000) == 0xc8400000)
                                            return OP_ldxr;
                                        if ((enc & 0xff000000) == 0xd8000000)
                                            return OP_prfm;
                                    }
                                } else {
                                    if ((enc >> 10 & 1) == 0) {
                                        if ((enc >> 24 & 1) == 0) {
                                            if ((enc & 0x9f000000) == 0x90000000)
                                                return OP_adrp;
                                            if ((enc & 0xffe00c00) == 0xf8400800)
                                                return OP_ldtr;
                                            if ((enc & 0xffe00c00) == 0xf8400000)
                                                return OP_ldur;
                                        } else {
                                            if ((enc & 0xffc00000) == 0xf9400000)
                                                return OP_ldr;
                                            if ((enc & 0x7f800000) == 0x71000000)
                                                return OP_subs;
                                        }
                                    } else {
                                        if ((enc >> 24 & 1) == 0) {
                                            if ((enc & 0x9f000000) == 0x90000000)
                                                return OP_adrp;
                                            if ((enc & 0xffe00c00) == 0xf8400400)
                                                return OP_ldr;
                                            if ((enc & 0xffe00c00) == 0xf8400c00)
                                                return OP_ldr;
                                        } else {
                                            if ((enc & 0xffc00000) == 0xf9400000)
                                                return OP_ldr;
                                            if ((enc & 0x7f800000) == 0x71000000)
                                                return OP_subs;
                                        }
                                    }
                                }
                            } else {
                                if ((enc >> 28 & 1) == 0) {
                                    if ((enc >> 24 & 1) == 0) {
                                        if ((enc & 0x7f200000) == 0x6a000000)
                                            return OP_ands;
                                        if ((enc & 0x7f200000) == 0x4a000000)
                                            return OP_eor;
                                    } else {
                                        if ((enc & 0x7f200000) == 0x4b000000)
                                            return OP_sub;
                                        if ((enc & 0x7f200000) == 0x6b000000)
                                            return OP_subs;
                                    }
                                } else {
                                    if ((enc >> 27 & 1) == 0) {
                                        if ((enc & 0x7f800000) == 0x72000000)
                                            return OP_ands;
                                        if ((enc & 0x7f800000) == 0x52000000)
                                            return OP_eor;
                                        if ((enc & 0xffc00000) == 0xd3400000)
                                            return OP_ubfm;
                                    } else {
                                        if ((enc & 0x7fe00c10) == 0x7a400000)
                                            return OP_ccmp;
                                        if ((enc & 0x7fe00c10) == 0x7a400800)
                                            return OP_ccmp;
                                    }
                                }
                            }
                        } else {
                            if ((enc >> 29 & 1) == 0) {
                                if ((enc >> 27 & 1) == 0) {
                                    if ((enc >> 24 & 1) == 0) {
                                        if ((enc & 0x9f000000) == 0x90000000)
                                            return OP_adrp;
                                        if ((enc & 0x7f800000) == 0x52000000)
                                            return OP_eor;
                                    } else {
                                        if ((enc & 0x7f800000) == 0x51000000)
                                            return OP_sub;
                                        if ((enc & 0xffc00000) == 0xd3400000)
                                            return OP_ubfm;
                                    }
                                } else {
                                    if ((enc >> 15 & 1) == 0) {
                                        if ((enc & 0x7f200000) == 0x4a200000)
                                            return OP_eon;
                                        if ((enc & 0xffe08000) == 0xc8600000)
                                            return OP_ldxp;
                                        if ((enc & 0xff000000) == 0xd8000000)
                                            return OP_prfm;
                                    } else {
                                        if ((enc & 0x7f200000) == 0x4a200000)
                                            return OP_eon;
                                        if ((enc & 0xffe08000) == 0xc8608000)
                                            return OP_ldaxp;
                                        if ((enc & 0xff000000) == 0xd8000000)
                                            return OP_prfm;
                                    }
                                }
                            } else {
                                if ((enc >> 12 & 1) == 0) {
                                    if ((enc >> 27 & 1) == 0) {
                                        if ((enc & 0x9f000000) == 0x90000000)
                                            return OP_adrp;
                                        if ((enc & 0x7f800000) == 0x72000000)
                                            return OP_ands;
                                        if ((enc & 0x7f800000) == 0x71000000)
                                            return OP_subs;
                                    } else {
                                        if ((enc >> 13 & 1) == 0) {
                                            if ((enc >> 11 & 1) == 0) {
                                                if ((enc >> 14 & 1) == 0) {
                                                    if ((enc >> 15 & 1) == 0) {
                                                        if ((enc & 0x7f200000) == 0x6a200000)
                                                            return OP_bics;
                                                        if ((enc & 0xffe0fc00) == 0xf8600000)
                                                            return OP_ldaddl;
                                                        if ((enc & 0xffc00000) == 0xf9400000)
                                                            return OP_ldr;
                                                    } else {
                                                        if ((enc & 0x7f200000) == 0x6a200000)
                                                            return OP_bics;
                                                        if ((enc & 0xffc00000) == 0xf9400000)
                                                            return OP_ldr;
                                                        if ((enc & 0xffe0fc00) == 0xf8608000)
                                                            return OP_swpl;
                                                    }
                                                } else {
                                                    if ((enc & 0x7f200000) == 0x6a200000)
                                                        return OP_bics;
                                                    if ((enc & 0xffc00000) == 0xf9400000)
                                                        return OP_ldr;
                                                    if ((enc & 0xffe0fc00) == 0xf8604000)
                                                        return OP_ldsmaxl;
                                                }
                                            } else {
                                                if ((enc & 0x7f200000) == 0x6a200000)
                                                    return OP_bics;
                                                if ((enc & 0xffe00c00) == 0xf8600800)
                                                    return OP_ldr;
                                                if ((enc & 0xffc00000) == 0xf9400000)
                                                    return OP_ldr;
                                            }
                                        } else {
                                            if ((enc >> 11 & 1) == 0) {
                                                if ((enc >> 14 & 1) == 0) {
                                                    if ((enc & 0x7f200000) == 0x6a200000)
                                                        return OP_bics;
                                                    if ((enc & 0xffe0fc00) == 0xf8602000)
                                                        return OP_ldeorl;
                                                    if ((enc & 0xffc00000) == 0xf9400000)
                                                        return OP_ldr;
                                                } else {
                                                    if ((enc & 0x7f200000) == 0x6a200000)
                                                        return OP_bics;
                                                    if ((enc & 0xffc00000) == 0xf9400000)
                                                        return OP_ldr;
                                                    if ((enc & 0xffe0fc00) == 0xf8606000)
                                                        return OP_ldumaxl;
                                                }
                                            } else {
                                                if ((enc & 0x7f200000) == 0x6a200000)
                                                    return OP_bics;
                                                if ((enc & 0xffe00c00) == 0xf8600800)
                                                    return OP_ldr;
                                                if ((enc & 0xffc00000) == 0xf9400000)
                                                    return OP_ldr;
                                            }
                                        }
                                    }
                                } else {
                                    if ((enc >> 27 & 1) == 0) {
                                        if ((enc & 0x9f000000) == 0x90000000)
                                            return OP_adrp;
                                        if ((enc & 0x7f800000) == 0x72000000)
                                            return OP_ands;
                                        if ((enc & 0x7f800000) == 0x71000000)
                                            return OP_subs;
                                    } else {
                                        if ((enc >> 13 & 1) == 0) {
                                            if ((enc >> 11 & 1) == 0) {
                                                if ((enc >> 14 & 1) == 0) {
                                                    if ((enc & 0x7f200000) == 0x6a200000)
                                                        return OP_bics;
                                                    if ((enc & 0xffe0fc00) == 0xf8601000)
                                                        return OP_ldclrl;
                                                    if ((enc & 0xffc00000) == 0xf9400000)
                                                        return OP_ldr;
                                                } else {
                                                    if ((enc & 0x7f200000) == 0x6a200000)
                                                        return OP_bics;
                                                    if ((enc & 0xffc00000) == 0xf9400000)
                                                        return OP_ldr;
                                                    if ((enc & 0xffe0fc00) == 0xf8605000)
                                                        return OP_ldsminl;
                                                }
                                            } else {
                                                if ((enc & 0x7f200000) == 0x6a200000)
                                                    return OP_bics;
                                                if ((enc & 0xffe00c00) == 0xf8600800)
                                                    return OP_ldr;
                                                if ((enc & 0xffc00000) == 0xf9400000)
                                                    return OP_ldr;
                                            }
                                        } else {
                                            if ((enc >> 11 & 1) == 0) {
                                                if ((enc >> 14 & 1) == 0) {
                                                    if ((enc & 0x7f200000) == 0x6a200000)
                                                        return OP_bics;
                                                    if ((enc & 0xffc00000) == 0xf9400000)
                                                        return OP_ldr;
                                                    if ((enc & 0xffe0fc00) == 0xf8603000)
                                                        return OP_ldsetl;
                                                } else {
                                                    if ((enc & 0x7f200000) == 0x6a200000)
                                                        return OP_bics;
                                                    if ((enc & 0xffc00000) == 0xf9400000)
                                                        return OP_ldr;
                                                    if ((enc & 0xffe0fc00) == 0xf8607000)
                                                        return OP_lduminl;
                                                }
                                            } else {
                                                if ((enc & 0x7f200000) == 0x6a200000)
                                                    return OP_bics;
                                                if ((enc & 0xffe00c00) == 0xf8600800)
                                                    return OP_ldr;
                                                if ((enc & 0xffc00000) == 0xf9400000)
                                                    return OP_ldr;
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                } else {
                    if ((enc >> 29 & 1) == 0) {
                        if ((enc >> 25 & 1) == 0) {
                            if ((enc >> 31 & 1) == 0) {
                                if ((enc >> 28 & 1) == 0) {
                                    if ((enc & 0xffe0fc00) == 0x48e07c00)
                                        return OP_casah;
                                    if ((enc & 0xffe0fc00) == 0x48e0fc00)
                                        return OP_casalh;
                                    if ((enc & 0xfffffc00) == 0x48dffc00)
                                        return OP_ldarh;
                                } else {
                                    if ((enc & 0x9f000000) == 0x10000000)
                                        return OP_adr;
                                    if ((enc & 0xff000000) == 0x58000000)
                                        return OP_ldr;
                                }
                            } else {
                                if ((enc >> 28 & 1) == 0) {
                                    if ((enc & 0xffe0fc00) == 0xc8e07c00)
                                        return OP_casa;
                                    if ((enc & 0xffe0fc00) == 0xc8e0fc00)
                                        return OP_casal;
                                    if ((enc & 0xfffffc00) == 0xc8dffc00)
                                        return OP_ldar;
                                } else {
                                    if ((enc & 0x9f000000) == 0x90000000)
                                        return OP_adrp;
                                    if ((enc & 0xff000000) == 0xd8000000)
                                        return OP_prfm;
                                }
                            }
                        } else {
                            if ((enc >> 10 & 1) == 0) {
                                if ((enc >> 28 & 1) == 0) {
                                    if ((enc & 0x7f200000) == 0x4a200000)
                                        return OP_eon;
                                    if ((enc & 0x7f200000) == 0x4a000000)
                                        return OP_eor;
                                    if ((enc & 0x7f200000) == 0x4b000000)
                                        return OP_sub;
                                } else {
                                    if ((enc >> 11 & 1) == 0) {
                                        if ((enc >> 27 & 1) == 0) {
                                            if ((enc & 0xff800000) == 0x52800000)
                                                return OP_movz;
                                            if ((enc & 0xff800000) == 0xd2800000)
                                                return OP_movz;
                                        } else {
                                            if ((enc & 0x7ffffc00) == 0x5ac01000)
                                                return OP_clz;
                                            if ((enc & 0x7ffffc00) == 0x5ac00000)
                                                return OP_rbit;
                                        }
                                    } else {
                                        if ((enc >> 27 & 1) == 0) {
                                            if ((enc & 0xff800000) == 0x52800000)
                                                return OP_movz;
                                            if ((enc & 0xff800000) == 0xd2800000)
                                                return OP_movz;
                                        } else {
                                            if ((enc & 0xfffffc00) == 0x5ac00800)
                                                return OP_rev;
                                            if ((enc & 0xfffffc00) == 0xdac00800)
                                                return OP_rev32;
                                        }
                                    }
                                }
                            } else {
                                if ((enc >> 28 & 1) == 0) {
                                    if ((enc & 0x7f200000) == 0x4a200000)
                                        return OP_eon;
                                    if ((enc & 0x7f200000) == 0x4a000000)
                                        return OP_eor;
                                    if ((enc & 0x7f200000) == 0x4b000000)
                                        return OP_sub;
                                } else {
                                    if ((enc >> 27 & 1) == 0) {
                                        if ((enc & 0xff800000) == 0x52800000)
                                            return OP_movz;
                                        if ((enc & 0xff800000) == 0xd2800000)
                                            return OP_movz;
                                    } else {
                                        if ((enc & 0x7ffffc00) == 0x5ac01400)
                                            return OP_cls;
                                        if ((enc & 0xfffffc00) == 0xdac00c00)
                                            return OP_rev;
                                        if ((enc & 0x7ffffc00) == 0x5ac00400)
                                            return OP_rev16;
                                    }
                                }
                            }
                        }
                    } else {
                        if ((enc >> 31 & 1) == 0) {
                            if ((enc >> 21 & 1) == 0) {
                                if ((enc >> 28 & 1) == 0) {
                                    if ((enc >> 24 & 1) == 0) {
                                        if ((enc & 0x7f200000) == 0x6a000000)
                                            return OP_ands;
                                        if ((enc & 0xffc00000) == 0x68c00000)
                                            return OP_ldpsw;
                                    } else {
                                        if ((enc & 0xffc00000) == 0x69c00000)
                                            return OP_ldpsw;
                                        if ((enc & 0x7f200000) == 0x6b000000)
                                            return OP_subs;
                                    }
                                } else {
                                    if ((enc >> 10 & 1) == 0) {
                                        if ((enc >> 27 & 1) == 0) {
                                            if ((enc & 0x9f000000) == 0x10000000)
                                                return OP_adr;
                                            if ((enc & 0xff800000) == 0x72800000)
                                                return OP_movk;
                                        } else {
                                            if ((enc & 0xffc00000) == 0x79c00000)
                                                return OP_ldrsh;
                                            if ((enc & 0xffe00c00) == 0x78c00800)
                                                return OP_ldtrsh;
                                            if ((enc & 0xffe00c00) == 0x78c00000)
                                                return OP_ldursh;
                                        }
                                    } else {
                                        if ((enc >> 27 & 1) == 0) {
                                            if ((enc & 0x9f000000) == 0x10000000)
                                                return OP_adr;
                                            if ((enc & 0xff800000) == 0x72800000)
                                                return OP_movk;
                                        } else {
                                            if ((enc & 0xffe00c00) == 0x78c00400)
                                                return OP_ldrsh;
                                            if ((enc & 0xffe00c00) == 0x78c00c00)
                                                return OP_ldrsh;
                                            if ((enc & 0xffc00000) == 0x79c00000)
                                                return OP_ldrsh;
                                        }
                                    }
                                }
                            } else {
                                if ((enc >> 12 & 1) == 0) {
                                    if ((enc >> 28 & 1) == 0) {
                                        if ((enc & 0x7f200000) == 0x6a200000)
                                            return OP_bics;
                                        if ((enc & 0xffc00000) == 0x68c00000)
                                            return OP_ldpsw;
                                        if ((enc & 0xffc00000) == 0x69c00000)
                                            return OP_ldpsw;
                                    } else {
                                        if ((enc >> 13 & 1) == 0) {
                                            if ((enc >> 27 & 1) == 0) {
                                                if ((enc & 0x9f000000) == 0x10000000)
                                                    return OP_adr;
                                                if ((enc & 0xff800000) == 0x72800000)
                                                    return OP_movk;
                                            } else {
                                                if ((enc >> 11 & 1) == 0) {
                                                    if ((enc >> 14 & 1) == 0) {
                                                        if ((enc & 0xffe0fc00) == 0x78e00000)
                                                            return OP_ldaddalh;
                                                        if ((enc & 0xffc00000) == 0x79c00000)
                                                            return OP_ldrsh;
                                                        if ((enc & 0xffe0fc00) == 0x78e08000)
                                                            return OP_swpalh;
                                                    } else {
                                                        if ((enc & 0xffc00000) == 0x79c00000)
                                                            return OP_ldrsh;
                                                        if ((enc & 0xffe0fc00) == 0x78e04000)
                                                            return OP_ldsmaxalh;
                                                    }
                                                } else {
                                                    if ((enc & 0xffe00c00) == 0x78e00800)
                                                        return OP_ldrsh;
                                                    if ((enc & 0xffc00000) == 0x79c00000)
                                                        return OP_ldrsh;
                                                }
                                            }
                                        } else {
                                            if ((enc >> 27 & 1) == 0) {
                                                if ((enc & 0x9f000000) == 0x10000000)
                                                    return OP_adr;
                                                if ((enc & 0xff800000) == 0x72800000)
                                                    return OP_movk;
                                            } else {
                                                if ((enc >> 11 & 1) == 0) {
                                                    if ((enc & 0xffe0fc00) == 0x78e02000)
                                                        return OP_ldeoralh;
                                                    if ((enc & 0xffc00000) == 0x79c00000)
                                                        return OP_ldrsh;
                                                    if ((enc & 0xffe0fc00) == 0x78e06000)
                                                        return OP_ldumaxalh;
                                                } else {
                                                    if ((enc & 0xffe00c00) == 0x78e00800)
                                                        return OP_ldrsh;
                                                    if ((enc & 0xffc00000) == 0x79c00000)
                                                        return OP_ldrsh;
                                                }
                                            }
                                        }
                                    }
                                } else {
                                    if ((enc >> 28 & 1) == 0) {
                                        if ((enc & 0x7f200000) == 0x6a200000)
                                            return OP_bics;
                                        if ((enc & 0xffc00000) == 0x68c00000)
                                            return OP_ldpsw;
                                        if ((enc & 0xffc00000) == 0x69c00000)
                                            return OP_ldpsw;
                                    } else {
                                        if ((enc >> 13 & 1) == 0) {
                                            if ((enc >> 27 & 1) == 0) {
                                                if ((enc & 0x9f000000) == 0x10000000)
                                                    return OP_adr;
                                                if ((enc & 0xff800000) == 0x72800000)
                                                    return OP_movk;
                                            } else {
                                                if ((enc >> 11 & 1) == 0) {
                                                    if ((enc & 0xffe0fc00) == 0x78e01000)
                                                        return OP_ldclralh;
                                                    if ((enc & 0xffc00000) == 0x79c00000)
                                                        return OP_ldrsh;
                                                    if ((enc & 0xffe0fc00) == 0x78e05000)
                                                        return OP_ldsminalh;
                                                } else {
                                                    if ((enc & 0xffe00c00) == 0x78e00800)
                                                        return OP_ldrsh;
                                                    if ((enc & 0xffc00000) == 0x79c00000)
                                                        return OP_ldrsh;
                                                }
                                            }
                                        } else {
                                            if ((enc >> 27 & 1) == 0) {
                                                if ((enc & 0x9f000000) == 0x10000000)
                                                    return OP_adr;
                                                if ((enc & 0xff800000) == 0x72800000)
                                                    return OP_movk;
                                            } else {
                                                if ((enc >> 11 & 1) == 0) {
                                                    if ((enc & 0xffc00000) == 0x79c00000)
                                                        return OP_ldrsh;
                                                    if ((enc & 0xffe0fc00) == 0x78e03000)
                                                        return OP_ldsetalh;
                                                    if ((enc & 0xffe0fc00) == 0x78e07000)
                                                        return OP_lduminalh;
                                                } else {
                                                    if ((enc & 0xffe00c00) == 0x78e00800)
                                                        return OP_ldrsh;
                                                    if ((enc & 0xffc00000) == 0x79c00000)
                                                        return OP_ldrsh;
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        } else {
                            if ((enc >> 12 & 1) == 0) {
                                if ((enc >> 25 & 1) == 0) {
                                    if ((enc >> 13 & 1) == 0) {
                                        if ((enc >> 14 & 1) == 0) {
                                            if ((enc & 0x9f000000) == 0x90000000)
                                                return OP_adrp;
                                            if ((enc & 0xffe0fc00) == 0xf8e00000)
                                                return OP_ldaddal;
                                            if ((enc & 0xffe0fc00) == 0xf8e08000)
                                                return OP_swpal;
                                        } else {
                                            if ((enc & 0x9f000000) == 0x90000000)
                                                return OP_adrp;
                                            if ((enc & 0xffe0fc00) == 0xf8e04000)
                                                return OP_ldsmaxal;
                                        }
                                    } else {
                                        if ((enc & 0x9f000000) == 0x90000000)
                                            return OP_adrp;
                                        if ((enc & 0xffe0fc00) == 0xf8e02000)
                                            return OP_ldeoral;
                                        if ((enc & 0xffe0fc00) == 0xf8e06000)
                                            return OP_ldumaxal;
                                    }
                                } else {
                                    if ((enc >> 21 & 1) == 0) {
                                        if ((enc & 0x7f200000) == 0x6a000000)
                                            return OP_ands;
                                        if ((enc & 0xff800000) == 0xf2800000)
                                            return OP_movk;
                                        if ((enc & 0x7f200000) == 0x6b000000)
                                            return OP_subs;
                                    } else {
                                        if ((enc & 0x7f200000) == 0x6a200000)
                                            return OP_bics;
                                        if ((enc & 0xff800000) == 0xf2800000)
                                            return OP_movk;
                                    }
                                }
                            } else {
                                if ((enc >> 25 & 1) == 0) {
                                    if ((enc >> 13 & 1) == 0) {
                                        if ((enc & 0x9f000000) == 0x90000000)
                                            return OP_adrp;
                                        if ((enc & 0xffe0fc00) == 0xf8e01000)
                                            return OP_ldclral;
                                        if ((enc & 0xffe0fc00) == 0xf8e05000)
                                            return OP_ldsminal;
                                    } else {
                                        if ((enc & 0x9f000000) == 0x90000000)
                                            return OP_adrp;
                                        if ((enc & 0xffe0fc00) == 0xf8e03000)
                                            return OP_ldsetal;
                                        if ((enc & 0xffe0fc00) == 0xf8e07000)
                                            return OP_lduminal;
                                    }
                                } else {
                                    if ((enc >> 21 & 1) == 0) {
                                        if ((enc & 0x7f200000) == 0x6a000000)
                                            return OP_ands;
                                        if ((enc & 0xff800000) == 0xf2800000)
                                            return OP_movk;
                                        if ((enc & 0x7f200000) == 0x6b000000)
                                            return OP_subs;
                                    } else {
                                        if ((enc & 0x7f200000) == 0x6a200000)
                                            return OP_bics;
                                        if ((enc & 0xff800000) == 0xf2800000)
                                            return OP_movk;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    } else {
        if ((enc >> 25 & 1) == 0) {
            if ((enc >> 24 & 1) == 0) {
                if ((enc >> 28 & 1) == 0) {
                    if ((enc >> 22 & 1) == 0) {
                        if ((enc >> 23 & 1) == 0) {
                            if ((enc >> 27 & 1) == 0) {
                                if ((enc >> 21 & 1) == 0) {
                                    if ((enc >> 16 & 1) == 0) {
                                        if ((enc & 0xff3fe000) == 0x041a0000)
                                            return OP_and;
                                        if ((enc & 0xff3fe000) == 0x04180000)
                                            return OP_orr;
                                    } else {
                                        if ((enc & 0xff3fe000) == 0x041b0000)
                                            return OP_bic;
                                        if ((enc & 0xff3fe000) == 0x04190000)
                                            return OP_eor;
                                    }
                                } else {
                                    if ((enc >> 10 & 1) == 0) {
                                        if ((enc & 0xff20fc00) == 0x04200000)
                                            return OP_add;
                                        if ((enc & 0xff20fc00) == 0x04201000)
                                            return OP_sqadd;
                                        if ((enc & 0xff20fc00) == 0x04201800)
                                            return OP_sqsub;
                                    } else {
                                        if ((enc & 0xff20fc00) == 0x04200400)
                                            return OP_sub;
                                        if ((enc & 0xff20fc00) == 0x04201400)
                                            return OP_uqadd;
                                        if ((enc & 0xff20fc00) == 0x04201c00)
                                            return OP_uqsub;
                                    }
                                }
                            } else {
                                if ((enc >> 13 & 1) == 0) {
                                    if ((enc >> 29 & 1) == 0) {
                                        if ((enc & 0xbffff000) == 0x0c008000)
                                            return OP_st2;
                                        if ((enc & 0xbffff000) == 0x0c004000)
                                            return OP_st3;
                                        if ((enc & 0xbffff000) == 0x0c000000)
                                            return OP_st4;
                                    } else {
                                        if ((enc & 0xffc00000) == 0x2c000000)
                                            return OP_stnp;
                                        if ((enc & 0xffc00000) == 0x6c000000)
                                            return OP_stnp;
                                        if ((enc & 0xffc00000) == 0xac000000)
                                            return OP_stnp;
                                    }
                                } else {
                                    if ((enc >> 29 & 1) == 0) {
                                        if ((enc >> 14 & 1) == 0) {
                                            if ((enc & 0xbffff000) == 0x0c002000)
                                                return OP_st1;
                                            if ((enc & 0xbffff000) == 0x0c00a000)
                                                return OP_st1;
                                        } else {
                                            if ((enc & 0xbffff000) == 0x0c006000)
                                                return OP_st1;
                                            if ((enc & 0xbffff000) == 0x0c007000)
                                                return OP_st1;
                                        }
                                    } else {
                                        if ((enc & 0xffc00000) == 0x2c000000)
                                            return OP_stnp;
                                        if ((enc & 0xffc00000) == 0x6c000000)
                                            return OP_stnp;
                                        if ((enc & 0xffc00000) == 0xac000000)
                                            return OP_stnp;
                                    }
                                }
                            }
                        } else {
                            if ((enc >> 27 & 1) == 0) {
                                if ((enc >> 21 & 1) == 0) {
                                    if ((enc >> 16 & 1) == 0) {
                                        if ((enc & 0xff3fe000) == 0x041a0000)
                                            return OP_and;
                                        if ((enc & 0xff3fe000) == 0x04180000)
                                            return OP_orr;
                                    } else {
                                        if ((enc & 0xff3fe000) == 0x041b0000)
                                            return OP_bic;
                                        if ((enc & 0xff3fe000) == 0x04190000)
                                            return OP_eor;
                                    }
                                } else {
                                    if ((enc >> 10 & 1) == 0) {
                                        if ((enc & 0xff20fc00) == 0x04200000)
                                            return OP_add;
                                        if ((enc & 0xff20fc00) == 0x04201000)
                                            return OP_sqadd;
                                        if ((enc & 0xff20fc00) == 0x04201800)
                                            return OP_sqsub;
                                    } else {
                                        if ((enc & 0xff20fc00) == 0x04200400)
                                            return OP_sub;
                                        if ((enc & 0xff20fc00) == 0x04201400)
                                            return OP_uqadd;
                                        if ((enc & 0xff20fc00) == 0x04201c00)
                                            return OP_uqsub;
                                    }
                                }
                            } else {
                                if ((enc >> 13 & 1) == 0) {
                                    if ((enc >> 29 & 1) == 0) {
                                        if ((enc & 0xbfe0f000) == 0x0c808000)
                                            return OP_st2;
                                        if ((enc & 0xbfe0f000) == 0x0c804000)
                                            return OP_st3;
                                        if ((enc & 0xbfe0f000) == 0x0c800000)
                                            return OP_st4;
                                    } else {
                                        if ((enc & 0xffc00000) == 0x2c800000)
                                            return OP_stp;
                                        if ((enc & 0xffc00000) == 0x6c800000)
                                            return OP_stp;
                                        if ((enc & 0xffc00000) == 0xac800000)
                                            return OP_stp;
                                    }
                                } else {
                                    if ((enc >> 29 & 1) == 0) {
                                        if ((enc >> 14 & 1) == 0) {
                                            if ((enc & 0xbfe0f000) == 0x0c802000)
                                                return OP_st1;
                                            if ((enc & 0xbfe0f000) == 0x0c80a000)
                                                return OP_st1;
                                        } else {
                                            if ((enc & 0xbfe0f000) == 0x0c806000)
                                                return OP_st1;
                                            if ((enc & 0xbfe0f000) == 0x0c807000)
                                                return OP_st1;
                                        }
                                    } else {
                                        if ((enc & 0xffc00000) == 0x2c800000)
                                            return OP_stp;
                                        if ((enc & 0xffc00000) == 0x6c800000)
                                            return OP_stp;
                                        if ((enc & 0xffc00000) == 0xac800000)
                                            return OP_stp;
                                    }
                                }
                            }
                        }
                    } else {
                        if ((enc >> 23 & 1) == 0) {
                            if ((enc >> 27 & 1) == 0) {
                                if ((enc >> 21 & 1) == 0) {
                                    if ((enc >> 16 & 1) == 0) {
                                        if ((enc & 0xff3fe000) == 0x041a0000)
                                            return OP_and;
                                        if ((enc & 0xff3fe000) == 0x04180000)
                                            return OP_orr;
                                    } else {
                                        if ((enc & 0xff3fe000) == 0x041b0000)
                                            return OP_bic;
                                        if ((enc & 0xff3fe000) == 0x04190000)
                                            return OP_eor;
                                    }
                                } else {
                                    if ((enc >> 10 & 1) == 0) {
                                        if ((enc & 0xff20fc00) == 0x04200000)
                                            return OP_add;
                                        if ((enc & 0xff20fc00) == 0x04201000)
                                            return OP_sqadd;
                                        if ((enc & 0xff20fc00) == 0x04201800)
                                            return OP_sqsub;
                                    } else {
                                        if ((enc & 0xff20fc00) == 0x04200400)
                                            return OP_sub;
                                        if ((enc & 0xff20fc00) == 0x04201400)
                                            return OP_uqadd;
                                        if ((enc & 0xff20fc00) == 0x04201c00)
                                            return OP_uqsub;
                                    }
                                }
                            } else {
                                if ((enc >> 13 & 1) == 0) {
                                    if ((enc >> 29 & 1) == 0) {
                                        if ((enc & 0xbffff000) == 0x0c408000)
                                            return OP_ld2;
                                        if ((enc & 0xbffff000) == 0x0c404000)
                                            return OP_ld3;
                                        if ((enc & 0xbffff000) == 0x0c400000)
                                            return OP_ld4;
                                    } else {
                                        if ((enc & 0xffc00000) == 0x2c400000)
                                            return OP_ldnp;
                                        if ((enc & 0xffc00000) == 0x6c400000)
                                            return OP_ldnp;
                                        if ((enc & 0xffc00000) == 0xac400000)
                                            return OP_ldnp;
                                    }
                                } else {
                                    if ((enc >> 29 & 1) == 0) {
                                        if ((enc >> 14 & 1) == 0) {
                                            if ((enc & 0xbffff000) == 0x0c402000)
                                                return OP_ld1;
                                            if ((enc & 0xbffff000) == 0x0c40a000)
                                                return OP_ld1;
                                        } else {
                                            if ((enc & 0xbffff000) == 0x0c406000)
                                                return OP_ld1;
                                            if ((enc & 0xbffff000) == 0x0c407000)
                                                return OP_ld1;
                                        }
                                    } else {
                                        if ((enc & 0xffc00000) == 0x2c400000)
                                            return OP_ldnp;
                                        if ((enc & 0xffc00000) == 0x6c400000)
                                            return OP_ldnp;
                                        if ((enc & 0xffc00000) == 0xac400000)
                                            return OP_ldnp;
                                    }
                                }
                            }
                        } else {
                            if ((enc >> 27 & 1) == 0) {
                                if ((enc >> 21 & 1) == 0) {
                                    if ((enc >> 16 & 1) == 0) {
                                        if ((enc & 0xff3fe000) == 0x041a0000)
                                            return OP_and;
                                        if ((enc & 0xff3fe000) == 0x04180000)
                                            return OP_orr;
                                    } else {
                                        if ((enc & 0xff3fe000) == 0x041b0000)
                                            return OP_bic;
                                        if ((enc & 0xff3fe000) == 0x04190000)
                                            return OP_eor;
                                    }
                                } else {
                                    if ((enc >> 10 & 1) == 0) {
                                        if ((enc & 0xff20fc00) == 0x04200000)
                                            return OP_add;
                                        if ((enc & 0xff20fc00) == 0x04201000)
                                            return OP_sqadd;
                                        if ((enc & 0xff20fc00) == 0x04201800)
                                            return OP_sqsub;
                                    } else {
                                        if ((enc & 0xff20fc00) == 0x04200400)
                                            return OP_sub;
                                        if ((enc & 0xff20fc00) == 0x04201400)
                                            return OP_uqadd;
                                        if ((enc & 0xff20fc00) == 0x04201c00)
                                            return OP_uqsub;
                                    }
                                }
                            } else {
                                if ((enc >> 13 & 1) == 0) {
                                    if ((enc >> 29 & 1) == 0) {
                                        if ((enc & 0xbfe0f000) == 0x0cc08000)
                                            return OP_ld2;
                                        if ((enc & 0xbfe0f000) == 0x0cc04000)
                                            return OP_ld3;
                                        if ((enc & 0xbfe0f000) == 0x0cc00000)
                                            return OP_ld4;
                                    } else {
                                        if ((enc & 0xffc00000) == 0x2cc00000)
                                            return OP_ldp;
                                        if ((enc & 0xffc00000) == 0x6cc00000)
                                            return OP_ldp;
                                        if ((enc & 0xffc00000) == 0xacc00000)
                                            return OP_ldp;
                                    }
                                } else {
                                    if ((enc >> 29 & 1) == 0) {
                                        if ((enc >> 14 & 1) == 0) {
                                            if ((enc & 0xbfe0f000) == 0x0cc02000)
                                                return OP_ld1;
                                            if ((enc & 0xbfe0f000) == 0x0cc0a000)
                                                return OP_ld1;
                                        } else {
                                            if ((enc & 0xbfe0f000) == 0x0cc06000)
                                                return OP_ld1;
                                            if ((enc & 0xbfe0f000) == 0x0cc07000)
                                                return OP_ld1;
                                        }
                                    } else {
                                        if ((enc & 0xffc00000) == 0x2cc00000)
                                            return OP_ldp;
                                        if ((enc & 0xffc00000) == 0x6cc00000)
                                            return OP_ldp;
                                        if ((enc & 0xffc00000) == 0xacc00000)
                                            return OP_ldp;
                                    }
                                }
                            }
                        }
                    }
                } else {
                    if ((enc >> 30 & 1) == 0) {
                        if ((enc >> 10 & 1) == 0) {
                            if ((enc >> 11 & 1) == 0) {
                                if ((enc >> 29 & 1) == 0) {
                                    if ((enc >> 27 & 1) == 0) {
                                        if ((enc & 0xfc000000) == 0x14000000)
                                            return OP_b;
                                        if ((enc & 0xfc000000) == 0x94000000)
                                            return OP_bl;
                                    } else {
                                        if ((enc & 0xff000000) == 0x1c000000)
                                            return OP_ldr;
                                        if ((enc & 0xff000000) == 0x9c000000)
                                            return OP_ldr;
                                    }
                                } else {
                                    if ((enc >> 22 & 1) == 0) {
                                        if ((enc >> 23 & 1) == 0) {
                                            if ((enc & 0x7f000000) == 0x34000000)
                                                return OP_cbz;
                                            if ((enc & 0xffe00c00) == 0x3c000000)
                                                return OP_stur;
                                            if ((enc & 0xffe00c00) == 0xbc000000)
                                                return OP_stur;
                                        } else {
                                            if ((enc & 0x7f000000) == 0x34000000)
                                                return OP_cbz;
                                            if ((enc & 0xffe00c00) == 0x3c800000)
                                                return OP_stur;
                                        }
                                    } else {
                                        if ((enc >> 23 & 1) == 0) {
                                            if ((enc & 0x7f000000) == 0x34000000)
                                                return OP_cbz;
                                            if ((enc & 0xffe00c00) == 0x3c400000)
                                                return OP_ldur;
                                            if ((enc & 0xffe00c00) == 0xbc400000)
                                                return OP_ldur;
                                        } else {
                                            if ((enc & 0x7f000000) == 0x34000000)
                                                return OP_cbz;
                                            if ((enc & 0xffe00c00) == 0x3cc00000)
                                                return OP_ldur;
                                        }
                                    }
                                }
                            } else {
                                if ((enc >> 29 & 1) == 0) {
                                    if ((enc >> 27 & 1) == 0) {
                                        if ((enc & 0xfc000000) == 0x14000000)
                                            return OP_b;
                                        if ((enc & 0xfc000000) == 0x94000000)
                                            return OP_bl;
                                    } else {
                                        if ((enc & 0xff000000) == 0x1c000000)
                                            return OP_ldr;
                                        if ((enc & 0xff000000) == 0x9c000000)
                                            return OP_ldr;
                                    }
                                } else {
                                    if ((enc >> 22 & 1) == 0) {
                                        if ((enc >> 23 & 1) == 0) {
                                            if ((enc & 0x7f000000) == 0x34000000)
                                                return OP_cbz;
                                            if ((enc & 0xffe00c00) == 0x3c200800)
                                                return OP_str;
                                            if ((enc & 0xffe00c00) == 0xbc200800)
                                                return OP_str;
                                        } else {
                                            if ((enc & 0x7f000000) == 0x34000000)
                                                return OP_cbz;
                                            if ((enc & 0xffe00c00) == 0x3ca00800)
                                                return OP_str;
                                        }
                                    } else {
                                        if ((enc >> 23 & 1) == 0) {
                                            if ((enc & 0x7f000000) == 0x34000000)
                                                return OP_cbz;
                                            if ((enc & 0xffe00c00) == 0x3c600800)
                                                return OP_ldr;
                                            if ((enc & 0xffe00c00) == 0xbc600800)
                                                return OP_ldr;
                                        } else {
                                            if ((enc & 0x7f000000) == 0x34000000)
                                                return OP_cbz;
                                            if ((enc & 0xffe00c00) == 0x3ce00800)
                                                return OP_ldr;
                                        }
                                    }
                                }
                            }
                        } else {
                            if ((enc >> 11 & 1) == 0) {
                                if ((enc >> 29 & 1) == 0) {
                                    if ((enc >> 27 & 1) == 0) {
                                        if ((enc & 0xfc000000) == 0x14000000)
                                            return OP_b;
                                        if ((enc & 0xfc000000) == 0x94000000)
                                            return OP_bl;
                                    } else {
                                        if ((enc & 0xff000000) == 0x1c000000)
                                            return OP_ldr;
                                        if ((enc & 0xff000000) == 0x9c000000)
                                            return OP_ldr;
                                    }
                                } else {
                                    if ((enc >> 22 & 1) == 0) {
                                        if ((enc >> 23 & 1) == 0) {
                                            if ((enc & 0x7f000000) == 0x34000000)
                                                return OP_cbz;
                                            if ((enc & 0xffe00c00) == 0x3c000400)
                                                return OP_str;
                                            if ((enc & 0xffe00c00) == 0xbc000400)
                                                return OP_str;
                                        } else {
                                            if ((enc & 0x7f000000) == 0x34000000)
                                                return OP_cbz;
                                            if ((enc & 0xffe00c00) == 0x3c800400)
                                                return OP_str;
                                        }
                                    } else {
                                        if ((enc >> 23 & 1) == 0) {
                                            if ((enc & 0x7f000000) == 0x34000000)
                                                return OP_cbz;
                                            if ((enc & 0xffe00c00) == 0x3c400400)
                                                return OP_ldr;
                                            if ((enc & 0xffe00c00) == 0xbc400400)
                                                return OP_ldr;
                                        } else {
                                            if ((enc & 0x7f000000) == 0x34000000)
                                                return OP_cbz;
                                            if ((enc & 0xffe00c00) == 0x3cc00400)
                                                return OP_ldr;
                                        }
                                    }
                                }
                            } else {
                                if ((enc >> 29 & 1) == 0) {
                                    if ((enc >> 27 & 1) == 0) {
                                        if ((enc & 0xfc000000) == 0x14000000)
                                            return OP_b;
                                        if ((enc & 0xfc000000) == 0x94000000)
                                            return OP_bl;
                                    } else {
                                        if ((enc & 0xff000000) == 0x1c000000)
                                            return OP_ldr;
                                        if ((enc & 0xff000000) == 0x9c000000)
                                            return OP_ldr;
                                    }
                                } else {
                                    if ((enc >> 22 & 1) == 0) {
                                        if ((enc >> 23 & 1) == 0) {
                                            if ((enc & 0x7f000000) == 0x34000000)
                                                return OP_cbz;
                                            if ((enc & 0xffe00c00) == 0x3c000c00)
                                                return OP_str;
                                            if ((enc & 0xffe00c00) == 0xbc000c00)
                                                return OP_str;
                                        } else {
                                            if ((enc & 0x7f000000) == 0x34000000)
                                                return OP_cbz;
                                            if ((enc & 0xffe00c00) == 0x3c800c00)
                                                return OP_str;
                                        }
                                    } else {
                                        if ((enc >> 23 & 1) == 0) {
                                            if ((enc & 0x7f000000) == 0x34000000)
                                                return OP_cbz;
                                            if ((enc & 0xffe00c00) == 0x3c400c00)
                                                return OP_ldr;
                                            if ((enc & 0xffe00c00) == 0xbc400c00)
                                                return OP_ldr;
                                        } else {
                                            if ((enc & 0x7f000000) == 0x34000000)
                                                return OP_cbz;
                                            if ((enc & 0xffe00c00) == 0x3cc00c00)
                                                return OP_ldr;
                                        }
                                    }
                                }
                            }
                        }
                    } else {
                        if ((enc >> 31 & 1) == 0) {
                            if ((enc >> 10 & 1) == 0) {
                                if ((enc >> 11 & 1) == 0) {
                                    if ((enc >> 29 & 1) == 0) {
                                        if ((enc & 0xff000010) == 0x54000000)
                                            return OP_bcond;
                                        if ((enc & 0xff000000) == 0x5c000000)
                                            return OP_ldr;
                                    } else {
                                        if ((enc & 0xffe00c00) == 0x7c400000)
                                            return OP_ldur;
                                        if ((enc & 0xffe00c00) == 0x7c000000)
                                            return OP_stur;
                                    }
                                } else {
                                    if ((enc >> 29 & 1) == 0) {
                                        if ((enc & 0xff000010) == 0x54000000)
                                            return OP_bcond;
                                        if ((enc & 0xff000000) == 0x5c000000)
                                            return OP_ldr;
                                    } else {
                                        if ((enc & 0xffe00c00) == 0x7c600800)
                                            return OP_ldr;
                                        if ((enc & 0xffe00c00) == 0x7c200800)
                                            return OP_str;
                                    }
                                }
                            } else {
                                if ((enc >> 11 & 1) == 0) {
                                    if ((enc >> 29 & 1) == 0) {
                                        if ((enc & 0xff000010) == 0x54000000)
                                            return OP_bcond;
                                        if ((enc & 0xff000000) == 0x5c000000)
                                            return OP_ldr;
                                    } else {
                                        if ((enc & 0xffe00c00) == 0x7c400400)
                                            return OP_ldr;
                                        if ((enc & 0xffe00c00) == 0x7c000400)
                                            return OP_str;
                                    }
                                } else {
                                    if ((enc >> 29 & 1) == 0) {
                                        if ((enc & 0xff000010) == 0x54000000)
                                            return OP_bcond;
                                        if ((enc & 0xff000000) == 0x5c000000)
                                            return OP_ldr;
                                    } else {
                                        if ((enc & 0xffe00c00) == 0x7c400c00)
                                            return OP_ldr;
                                        if ((enc & 0xffe00c00) == 0x7c000c00)
                                            return OP_str;
                                    }
                                }
                            }
                        } else {
                            if ((enc >> 22 & 1) == 0) {
                                if ((enc >> 27 & 1) == 0) {
                                    if ((enc >> 0 & 1) == 0) {
                                        if ((enc & 0xffe0001f) == 0xd4200000)
                                            return OP_brk;
                                        if ((enc & 0xffe0001f) == 0xd4000002)
                                            return OP_hvc;
                                    } else {
                                        if ((enc & 0xffe0001f) == 0xd4000003)
                                            return OP_smc;
                                        if ((enc & 0xffe0001f) == 0xd4000001)
                                            return OP_svc;
                                    }
                                } else {
                                    if ((enc >> 10 & 1) == 0) {
                                        if ((enc & 0xffe00c00) == 0xfc200800)
                                            return OP_str;
                                        if ((enc & 0xffe00c00) == 0xfc000000)
                                            return OP_stur;
                                    } else {
                                        if ((enc & 0xffe00c00) == 0xfc000400)
                                            return OP_str;
                                        if ((enc & 0xffe00c00) == 0xfc000c00)
                                            return OP_str;
                                    }
                                }
                            } else {
                                if ((enc >> 10 & 1) == 0) {
                                    if ((enc & 0xffe0001f) == 0xd4400000)
                                        return OP_hlt;
                                    if ((enc & 0xffe00c00) == 0xfc600800)
                                        return OP_ldr;
                                    if ((enc & 0xffe00c00) == 0xfc400000)
                                        return OP_ldur;
                                } else {
                                    if ((enc & 0xffe0001f) == 0xd4400000)
                                        return OP_hlt;
                                    if ((enc & 0xffe00c00) == 0xfc400400)
                                        return OP_ldr;
                                    if ((enc & 0xffe00c00) == 0xfc400c00)
                                        return OP_ldr;
                                }
                            }
                        }
                    }
                }
            } else {
                if ((enc >> 22 & 1) == 0) {
                    if ((enc >> 28 & 1) == 0) {
                        if ((enc >> 23 & 1) == 0) {
                            if ((enc >> 13 & 1) == 0) {
                                if ((enc >> 15 & 1) == 0) {
                                    if ((enc >> 29 & 1) == 0) {
                                        if ((enc >> 14 & 1) == 0) {
                                            if ((enc & 0xbfffe000) == 0x0d000000)
                                                return OP_st1;
                                            if ((enc & 0xbfffe000) == 0x0d200000)
                                                return OP_st2;
                                        } else {
                                            if ((enc & 0xbfffe400) == 0x0d004000)
                                                return OP_st1;
                                            if ((enc & 0xbfffe400) == 0x0d204000)
                                                return OP_st2;
                                        }
                                    } else {
                                        if ((enc & 0xffc00000) == 0x2d000000)
                                            return OP_stp;
                                        if ((enc & 0xffc00000) == 0x6d000000)
                                            return OP_stp;
                                        if ((enc & 0xffc00000) == 0xad000000)
                                            return OP_stp;
                                    }
                                } else {
                                    if ((enc >> 29 & 1) == 0) {
                                        if ((enc >> 10 & 1) == 0) {
                                            if ((enc & 0xbfffec00) == 0x0d008000)
                                                return OP_st1;
                                            if ((enc & 0xbfffec00) == 0x0d208000)
                                                return OP_st2;
                                        } else {
                                            if ((enc & 0xbffffc00) == 0x0d008400)
                                                return OP_st1;
                                            if ((enc & 0xbffffc00) == 0x0d208400)
                                                return OP_st2;
                                        }
                                    } else {
                                        if ((enc & 0xffc00000) == 0x2d000000)
                                            return OP_stp;
                                        if ((enc & 0xffc00000) == 0x6d000000)
                                            return OP_stp;
                                        if ((enc & 0xffc00000) == 0xad000000)
                                            return OP_stp;
                                    }
                                }
                            } else {
                                if ((enc >> 15 & 1) == 0) {
                                    if ((enc >> 29 & 1) == 0) {
                                        if ((enc >> 14 & 1) == 0) {
                                            if ((enc & 0xbfffe000) == 0x0d002000)
                                                return OP_st3;
                                            if ((enc & 0xbfffe000) == 0x0d202000)
                                                return OP_st4;
                                        } else {
                                            if ((enc & 0xbfffe400) == 0x0d006000)
                                                return OP_st3;
                                            if ((enc & 0xbfffe400) == 0x0d206000)
                                                return OP_st4;
                                        }
                                    } else {
                                        if ((enc & 0xffc00000) == 0x2d000000)
                                            return OP_stp;
                                        if ((enc & 0xffc00000) == 0x6d000000)
                                            return OP_stp;
                                        if ((enc & 0xffc00000) == 0xad000000)
                                            return OP_stp;
                                    }
                                } else {
                                    if ((enc >> 29 & 1) == 0) {
                                        if ((enc >> 10 & 1) == 0) {
                                            if ((enc & 0xbfffec00) == 0x0d00a000)
                                                return OP_st3;
                                            if ((enc & 0xbfffec00) == 0x0d20a000)
                                                return OP_st4;
                                        } else {
                                            if ((enc & 0xbffffc00) == 0x0d00a400)
                                                return OP_st3;
                                            if ((enc & 0xbffffc00) == 0x0d20a400)
                                                return OP_st4;
                                        }
                                    } else {
                                        if ((enc & 0xffc00000) == 0x2d000000)
                                            return OP_stp;
                                        if ((enc & 0xffc00000) == 0x6d000000)
                                            return OP_stp;
                                        if ((enc & 0xffc00000) == 0xad000000)
                                            return OP_stp;
                                    }
                                }
                            }
                        } else {
                            if ((enc >> 13 & 1) == 0) {
                                if ((enc >> 15 & 1) == 0) {
                                    if ((enc >> 29 & 1) == 0) {
                                        if ((enc >> 14 & 1) == 0) {
                                            if ((enc & 0xbfe0e000) == 0x0d800000)
                                                return OP_st1;
                                            if ((enc & 0xbfe0e000) == 0x0da00000)
                                                return OP_st2;
                                        } else {
                                            if ((enc & 0xbfe0e400) == 0x0d804000)
                                                return OP_st1;
                                            if ((enc & 0xbfe0e400) == 0x0da04000)
                                                return OP_st2;
                                        }
                                    } else {
                                        if ((enc & 0xffc00000) == 0x2d800000)
                                            return OP_stp;
                                        if ((enc & 0xffc00000) == 0x6d800000)
                                            return OP_stp;
                                        if ((enc & 0xffc00000) == 0xad800000)
                                            return OP_stp;
                                    }
                                } else {
                                    if ((enc >> 29 & 1) == 0) {
                                        if ((enc >> 10 & 1) == 0) {
                                            if ((enc & 0xbfe0ec00) == 0x0d808000)
                                                return OP_st1;
                                            if ((enc & 0xbfe0ec00) == 0x0da08000)
                                                return OP_st2;
                                        } else {
                                            if ((enc & 0xbfe0fc00) == 0x0d808400)
                                                return OP_st1;
                                            if ((enc & 0xbfe0fc00) == 0x0da08400)
                                                return OP_st2;
                                        }
                                    } else {
                                        if ((enc & 0xffc00000) == 0x2d800000)
                                            return OP_stp;
                                        if ((enc & 0xffc00000) == 0x6d800000)
                                            return OP_stp;
                                        if ((enc & 0xffc00000) == 0xad800000)
                                            return OP_stp;
                                    }
                                }
                            } else {
                                if ((enc >> 15 & 1) == 0) {
                                    if ((enc >> 29 & 1) == 0) {
                                        if ((enc >> 14 & 1) == 0) {
                                            if ((enc & 0xbfe0e000) == 0x0d802000)
                                                return OP_st3;
                                            if ((enc & 0xbfe0e000) == 0x0da02000)
                                                return OP_st4;
                                        } else {
                                            if ((enc & 0xbfe0e400) == 0x0d806000)
                                                return OP_st3;
                                            if ((enc & 0xbfe0e400) == 0x0da06000)
                                                return OP_st4;
                                        }
                                    } else {
                                        if ((enc & 0xffc00000) == 0x2d800000)
                                            return OP_stp;
                                        if ((enc & 0xffc00000) == 0x6d800000)
                                            return OP_stp;
                                        if ((enc & 0xffc00000) == 0xad800000)
                                            return OP_stp;
                                    }
                                } else {
                                    if ((enc >> 29 & 1) == 0) {
                                        if ((enc >> 10 & 1) == 0) {
                                            if ((enc & 0xbfe0ec00) == 0x0d80a000)
                                                return OP_st3;
                                            if ((enc & 0xbfe0ec00) == 0x0da0a000)
                                                return OP_st4;
                                        } else {
                                            if ((enc & 0xbfe0fc00) == 0x0d80a400)
                                                return OP_st3;
                                            if ((enc & 0xbfe0fc00) == 0x0da0a400)
                                                return OP_st4;
                                        }
                                    } else {
                                        if ((enc & 0xffc00000) == 0x2d800000)
                                            return OP_stp;
                                        if ((enc & 0xffc00000) == 0x6d800000)
                                            return OP_stp;
                                        if ((enc & 0xffc00000) == 0xad800000)
                                            return OP_stp;
                                    }
                                }
                            }
                        }
                    } else {
                        if ((enc >> 29 & 1) == 0) {
                            if ((enc >> 7 & 1) == 0) {
                                if ((enc >> 5 & 1) == 0) {
                                    if ((enc >> 20 & 1) == 0) {
                                        if ((enc >> 30 & 1) == 0) {
                                            if ((enc & 0xfc000000) == 0x14000000)
                                                return OP_b;
                                            if ((enc & 0xfc000000) == 0x94000000)
                                                return OP_bl;
                                        } else {
                                            if ((enc >> 6 & 1) == 0) {
                                                if ((enc & 0xffffffff) == 0xd503201f)
                                                    return OP_nop;
                                                if ((enc & 0xfff80000) == 0xd5080000)
                                                    return OP_sys;
                                            } else {
                                                if ((enc & 0xfffff0ff) == 0xd503305f)
                                                    return OP_clrex;
                                                if ((enc & 0xfff80000) == 0xd5080000)
                                                    return OP_sys;
                                                if ((enc & 0xffffffff) == 0xd503205f)
                                                    return OP_wfe;
                                            }
                                        }
                                    } else {
                                        if ((enc >> 30 & 1) == 0) {
                                            if ((enc & 0xfc000000) == 0x14000000)
                                                return OP_b;
                                            if ((enc & 0xfc000000) == 0x94000000)
                                                return OP_bl;
                                        } else {
                                            if ((enc & 0xfff00000) == 0xd5300000)
                                                return OP_mrs;
                                            if ((enc & 0xfff00000) == 0xd5100000)
                                                return OP_msr;
                                        }
                                    }
                                } else {
                                    if ((enc >> 20 & 1) == 0) {
                                        if ((enc >> 30 & 1) == 0) {
                                            if ((enc & 0xfc000000) == 0x14000000)
                                                return OP_b;
                                            if ((enc & 0xfc000000) == 0x94000000)
                                                return OP_bl;
                                        } else {
                                            if ((enc & 0xfff80000) == 0xd5080000)
                                                return OP_sys;
                                            if ((enc & 0xffffffff) == 0xd503207f)
                                                return OP_wfi;
                                            if ((enc & 0xffffffff) == 0xd503203f)
                                                return OP_yield;
                                        }
                                    } else {
                                        if ((enc >> 30 & 1) == 0) {
                                            if ((enc & 0xfc000000) == 0x14000000)
                                                return OP_b;
                                            if ((enc & 0xfc000000) == 0x94000000)
                                                return OP_bl;
                                        } else {
                                            if ((enc & 0xfff00000) == 0xd5300000)
                                                return OP_mrs;
                                            if ((enc & 0xfff00000) == 0xd5100000)
                                                return OP_msr;
                                        }
                                    }
                                }
                            } else {
                                if ((enc >> 5 & 1) == 0) {
                                    if ((enc >> 20 & 1) == 0) {
                                        if ((enc >> 30 & 1) == 0) {
                                            if ((enc & 0xfc000000) == 0x14000000)
                                                return OP_b;
                                            if ((enc & 0xfc000000) == 0x94000000)
                                                return OP_bl;
                                        } else {
                                            if ((enc >> 6 & 1) == 0) {
                                                if ((enc & 0xfffff0ff) == 0xd503309f)
                                                    return OP_dsb;
                                                if ((enc & 0xffffffff) == 0xd503209f)
                                                    return OP_sev;
                                                if ((enc & 0xfff80000) == 0xd5080000)
                                                    return OP_sys;
                                            } else {
                                                if ((enc & 0xfffff0ff) == 0xd50330df)
                                                    return OP_isb;
                                                if ((enc & 0xfff80000) == 0xd5080000)
                                                    return OP_sys;
                                            }
                                        }
                                    } else {
                                        if ((enc >> 30 & 1) == 0) {
                                            if ((enc & 0xfc000000) == 0x14000000)
                                                return OP_b;
                                            if ((enc & 0xfc000000) == 0x94000000)
                                                return OP_bl;
                                        } else {
                                            if ((enc & 0xfff00000) == 0xd5300000)
                                                return OP_mrs;
                                            if ((enc & 0xfff00000) == 0xd5100000)
                                                return OP_msr;
                                        }
                                    }
                                } else {
                                    if ((enc >> 20 & 1) == 0) {
                                        if ((enc >> 30 & 1) == 0) {
                                            if ((enc & 0xfc000000) == 0x14000000)
                                                return OP_b;
                                            if ((enc & 0xfc000000) == 0x94000000)
                                                return OP_bl;
                                        } else {
                                            if ((enc & 0xfffff0ff) == 0xd50330bf)
                                                return OP_dmb;
                                            if ((enc & 0xffffffff) == 0xd50320bf)
                                                return OP_sevl;
                                            if ((enc & 0xfff80000) == 0xd5080000)
                                                return OP_sys;
                                        }
                                    } else {
                                        if ((enc >> 30 & 1) == 0) {
                                            if ((enc & 0xfc000000) == 0x14000000)
                                                return OP_b;
                                            if ((enc & 0xfc000000) == 0x94000000)
                                                return OP_bl;
                                        } else {
                                            if ((enc & 0xfff00000) == 0xd5300000)
                                                return OP_mrs;
                                            if ((enc & 0xfff00000) == 0xd5100000)
                                                return OP_msr;
                                        }
                                    }
                                }
                            }
                        } else {
                            if ((enc >> 30 & 1) == 0) {
                                if ((enc >> 23 & 1) == 0) {
                                    if ((enc & 0x7f000000) == 0x35000000)
                                        return OP_cbnz;
                                    if ((enc & 0xffc00000) == 0x3d000000)
                                        return OP_str;
                                    if ((enc & 0xffc00000) == 0xbd000000)
                                        return OP_str;
                                } else {
                                    if ((enc & 0x7f000000) == 0x35000000)
                                        return OP_cbnz;
                                    if ((enc & 0xffc00000) == 0x3d800000)
                                        return OP_str;
                                }
                            } else {
                                if ((enc & 0xffc00000) == 0x7d000000)
                                    return OP_str;
                                if ((enc & 0xffc00000) == 0xfd000000)
                                    return OP_str;
                            }
                        }
                    }
                } else {
                    if ((enc >> 23 & 1) == 0) {
                        if ((enc >> 13 & 1) == 0) {
                            if ((enc >> 29 & 1) == 0) {
                                if ((enc >> 21 & 1) == 0) {
                                    if ((enc >> 14 & 1) == 0) {
                                        if ((enc >> 27 & 1) == 0) {
                                            if ((enc & 0xfc000000) == 0x14000000)
                                                return OP_b;
                                            if ((enc & 0xfc000000) == 0x94000000)
                                                return OP_bl;
                                        } else {
                                            if ((enc & 0xbfffe000) == 0x0d400000)
                                                return OP_ld1;
                                            if ((enc & 0xbfffec00) == 0x0d408000)
                                                return OP_ld1;
                                            if ((enc & 0xbffffc00) == 0x0d408400)
                                                return OP_ld1;
                                        }
                                    } else {
                                        if ((enc >> 27 & 1) == 0) {
                                            if ((enc & 0xfc000000) == 0x14000000)
                                                return OP_b;
                                            if ((enc & 0xfc000000) == 0x94000000)
                                                return OP_bl;
                                        } else {
                                            if ((enc & 0xbfffe400) == 0x0d404000)
                                                return OP_ld1;
                                            if ((enc & 0xbffff000) == 0x0d40c000)
                                                return OP_ld1r;
                                        }
                                    }
                                } else {
                                    if ((enc >> 14 & 1) == 0) {
                                        if ((enc >> 27 & 1) == 0) {
                                            if ((enc & 0xfc000000) == 0x14000000)
                                                return OP_b;
                                            if ((enc & 0xfc000000) == 0x94000000)
                                                return OP_bl;
                                        } else {
                                            if ((enc & 0xbfffe000) == 0x0d600000)
                                                return OP_ld2;
                                            if ((enc & 0xbfffec00) == 0x0d608000)
                                                return OP_ld2;
                                            if ((enc & 0xbffffc00) == 0x0d608400)
                                                return OP_ld2;
                                        }
                                    } else {
                                        if ((enc >> 27 & 1) == 0) {
                                            if ((enc & 0xfc000000) == 0x14000000)
                                                return OP_b;
                                            if ((enc & 0xfc000000) == 0x94000000)
                                                return OP_bl;
                                        } else {
                                            if ((enc & 0xbfffe400) == 0x0d604000)
                                                return OP_ld2;
                                            if ((enc & 0xbffff000) == 0x0d60c000)
                                                return OP_ld2r;
                                        }
                                    }
                                }
                            } else {
                                if ((enc >> 28 & 1) == 0) {
                                    if ((enc & 0xffc00000) == 0x2d400000)
                                        return OP_ldp;
                                    if ((enc & 0xffc00000) == 0x6d400000)
                                        return OP_ldp;
                                    if ((enc & 0xffc00000) == 0xad400000)
                                        return OP_ldp;
                                } else {
                                    if ((enc >> 30 & 1) == 0) {
                                        if ((enc & 0x7f000000) == 0x35000000)
                                            return OP_cbnz;
                                        if ((enc & 0xffc00000) == 0x3d400000)
                                            return OP_ldr;
                                        if ((enc & 0xffc00000) == 0xbd400000)
                                            return OP_ldr;
                                    } else {
                                        if ((enc & 0xffc00000) == 0x7d400000)
                                            return OP_ldr;
                                        if ((enc & 0xffc00000) == 0xfd400000)
                                            return OP_ldr;
                                    }
                                }
                            }
                        } else {
                            if ((enc >> 29 & 1) == 0) {
                                if ((enc >> 21 & 1) == 0) {
                                    if ((enc >> 14 & 1) == 0) {
                                        if ((enc >> 27 & 1) == 0) {
                                            if ((enc & 0xfc000000) == 0x14000000)
                                                return OP_b;
                                            if ((enc & 0xfc000000) == 0x94000000)
                                                return OP_bl;
                                        } else {
                                            if ((enc & 0xbfffe000) == 0x0d402000)
                                                return OP_ld3;
                                            if ((enc & 0xbfffec00) == 0x0d40a000)
                                                return OP_ld3;
                                            if ((enc & 0xbffffc00) == 0x0d40a400)
                                                return OP_ld3;
                                        }
                                    } else {
                                        if ((enc >> 27 & 1) == 0) {
                                            if ((enc & 0xfc000000) == 0x14000000)
                                                return OP_b;
                                            if ((enc & 0xfc000000) == 0x94000000)
                                                return OP_bl;
                                        } else {
                                            if ((enc & 0xbfffe400) == 0x0d406000)
                                                return OP_ld3;
                                            if ((enc & 0xbffff000) == 0x0d40e000)
                                                return OP_ld3r;
                                        }
                                    }
                                } else {
                                    if ((enc >> 14 & 1) == 0) {
                                        if ((enc >> 27 & 1) == 0) {
                                            if ((enc & 0xfc000000) == 0x14000000)
                                                return OP_b;
                                            if ((enc & 0xfc000000) == 0x94000000)
                                                return OP_bl;
                                        } else {
                                            if ((enc & 0xbfffe000) == 0x0d602000)
                                                return OP_ld4;
                                            if ((enc & 0xbfffec00) == 0x0d60a000)
                                                return OP_ld4;
                                            if ((enc & 0xbffffc00) == 0x0d60a400)
                                                return OP_ld4;
                                        }
                                    } else {
                                        if ((enc >> 27 & 1) == 0) {
                                            if ((enc & 0xfc000000) == 0x14000000)
                                                return OP_b;
                                            if ((enc & 0xfc000000) == 0x94000000)
                                                return OP_bl;
                                        } else {
                                            if ((enc & 0xbfffe400) == 0x0d606000)
                                                return OP_ld4;
                                            if ((enc & 0xbffff000) == 0x0d60e000)
                                                return OP_ld4r;
                                        }
                                    }
                                }
                            } else {
                                if ((enc >> 28 & 1) == 0) {
                                    if ((enc & 0xffc00000) == 0x2d400000)
                                        return OP_ldp;
                                    if ((enc & 0xffc00000) == 0x6d400000)
                                        return OP_ldp;
                                    if ((enc & 0xffc00000) == 0xad400000)
                                        return OP_ldp;
                                } else {
                                    if ((enc >> 30 & 1) == 0) {
                                        if ((enc & 0x7f000000) == 0x35000000)
                                            return OP_cbnz;
                                        if ((enc & 0xffc00000) == 0x3d400000)
                                            return OP_ldr;
                                        if ((enc & 0xffc00000) == 0xbd400000)
                                            return OP_ldr;
                                    } else {
                                        if ((enc & 0xffc00000) == 0x7d400000)
                                            return OP_ldr;
                                        if ((enc & 0xffc00000) == 0xfd400000)
                                            return OP_ldr;
                                    }
                                }
                            }
                        }
                    } else {
                        if ((enc >> 13 & 1) == 0) {
                            if ((enc >> 21 & 1) == 0) {
                                if ((enc >> 29 & 1) == 0) {
                                    if ((enc >> 14 & 1) == 0) {
                                        if ((enc >> 27 & 1) == 0) {
                                            if ((enc & 0xfc000000) == 0x14000000)
                                                return OP_b;
                                            if ((enc & 0xfc000000) == 0x94000000)
                                                return OP_bl;
                                        } else {
                                            if ((enc & 0xbfe0e000) == 0x0dc00000)
                                                return OP_ld1;
                                            if ((enc & 0xbfe0ec00) == 0x0dc08000)
                                                return OP_ld1;
                                            if ((enc & 0xbfe0fc00) == 0x0dc08400)
                                                return OP_ld1;
                                        }
                                    } else {
                                        if ((enc >> 27 & 1) == 0) {
                                            if ((enc & 0xfc000000) == 0x14000000)
                                                return OP_b;
                                            if ((enc & 0xfc000000) == 0x94000000)
                                                return OP_bl;
                                        } else {
                                            if ((enc & 0xbfe0e400) == 0x0dc04000)
                                                return OP_ld1;
                                            if ((enc & 0xbfe0f000) == 0x0dc0c000)
                                                return OP_ld1r;
                                        }
                                    }
                                } else {
                                    if ((enc >> 28 & 1) == 0) {
                                        if ((enc & 0xffc00000) == 0x2dc00000)
                                            return OP_ldp;
                                        if ((enc & 0xffc00000) == 0x6dc00000)
                                            return OP_ldp;
                                        if ((enc & 0xffc00000) == 0xadc00000)
                                            return OP_ldp;
                                    } else {
                                        if ((enc & 0x7f000000) == 0x35000000)
                                            return OP_cbnz;
                                        if ((enc & 0xffc00000) == 0x3dc00000)
                                            return OP_ldr;
                                    }
                                }
                            } else {
                                if ((enc >> 29 & 1) == 0) {
                                    if ((enc >> 14 & 1) == 0) {
                                        if ((enc >> 27 & 1) == 0) {
                                            if ((enc & 0xfc000000) == 0x14000000)
                                                return OP_b;
                                            if ((enc & 0xfc000000) == 0x94000000)
                                                return OP_bl;
                                        } else {
                                            if ((enc & 0xbfe0e000) == 0x0de00000)
                                                return OP_ld2;
                                            if ((enc & 0xbfe0ec00) == 0x0de08000)
                                                return OP_ld2;
                                            if ((enc & 0xbfe0fc00) == 0x0de08400)
                                                return OP_ld2;
                                        }
                                    } else {
                                        if ((enc >> 27 & 1) == 0) {
                                            if ((enc & 0xfc000000) == 0x14000000)
                                                return OP_b;
                                            if ((enc & 0xfc000000) == 0x94000000)
                                                return OP_bl;
                                        } else {
                                            if ((enc & 0xbfe0e400) == 0x0de04000)
                                                return OP_ld2;
                                            if ((enc & 0xbfe0f000) == 0x0de0c000)
                                                return OP_ld2r;
                                        }
                                    }
                                } else {
                                    if ((enc >> 28 & 1) == 0) {
                                        if ((enc & 0xffc00000) == 0x2dc00000)
                                            return OP_ldp;
                                        if ((enc & 0xffc00000) == 0x6dc00000)
                                            return OP_ldp;
                                        if ((enc & 0xffc00000) == 0xadc00000)
                                            return OP_ldp;
                                    } else {
                                        if ((enc & 0x7f000000) == 0x35000000)
                                            return OP_cbnz;
                                        if ((enc & 0xffc00000) == 0x3dc00000)
                                            return OP_ldr;
                                    }
                                }
                            }
                        } else {
                            if ((enc >> 21 & 1) == 0) {
                                if ((enc >> 29 & 1) == 0) {
                                    if ((enc >> 14 & 1) == 0) {
                                        if ((enc >> 27 & 1) == 0) {
                                            if ((enc & 0xfc000000) == 0x14000000)
                                                return OP_b;
                                            if ((enc & 0xfc000000) == 0x94000000)
                                                return OP_bl;
                                        } else {
                                            if ((enc & 0xbfe0e000) == 0x0dc02000)
                                                return OP_ld3;
                                            if ((enc & 0xbfe0ec00) == 0x0dc0a000)
                                                return OP_ld3;
                                            if ((enc & 0xbfe0fc00) == 0x0dc0a400)
                                                return OP_ld3;
                                        }
                                    } else {
                                        if ((enc >> 27 & 1) == 0) {
                                            if ((enc & 0xfc000000) == 0x14000000)
                                                return OP_b;
                                            if ((enc & 0xfc000000) == 0x94000000)
                                                return OP_bl;
                                        } else {
                                            if ((enc & 0xbfe0e400) == 0x0dc06000)
                                                return OP_ld3;
                                            if ((enc & 0xbfe0f000) == 0x0dc0e000)
                                                return OP_ld3r;
                                        }
                                    }
                                } else {
                                    if ((enc >> 28 & 1) == 0) {
                                        if ((enc & 0xffc00000) == 0x2dc00000)
                                            return OP_ldp;
                                        if ((enc & 0xffc00000) == 0x6dc00000)
                                            return OP_ldp;
                                        if ((enc & 0xffc00000) == 0xadc00000)
                                            return OP_ldp;
                                    } else {
                                        if ((enc & 0x7f000000) == 0x35000000)
                                            return OP_cbnz;
                                        if ((enc & 0xffc00000) == 0x3dc00000)
                                            return OP_ldr;
                                    }
                                }
                            } else {
                                if ((enc >> 29 & 1) == 0) {
                                    if ((enc >> 14 & 1) == 0) {
                                        if ((enc >> 27 & 1) == 0) {
                                            if ((enc & 0xfc000000) == 0x14000000)
                                                return OP_b;
                                            if ((enc & 0xfc000000) == 0x94000000)
                                                return OP_bl;
                                        } else {
                                            if ((enc & 0xbfe0e000) == 0x0de02000)
                                                return OP_ld4;
                                            if ((enc & 0xbfe0ec00) == 0x0de0a000)
                                                return OP_ld4;
                                            if ((enc & 0xbfe0fc00) == 0x0de0a400)
                                                return OP_ld4;
                                        }
                                    } else {
                                        if ((enc >> 27 & 1) == 0) {
                                            if ((enc & 0xfc000000) == 0x14000000)
                                                return OP_b;
                                            if ((enc & 0xfc000000) == 0x94000000)
                                                return OP_bl;
                                        } else {
                                            if ((enc & 0xbfe0e400) == 0x0de06000)
                                                return OP_ld4;
                                            if ((enc & 0xbfe0f000) == 0x0de0e000)
                                                return OP_ld4r;
                                        }
                                    }
                                } else {
                                    if ((enc >> 28 & 1) == 0) {
                                        if ((enc & 0xffc00000) == 0x2dc00000)
                                            return OP_ldp;
                                        if ((enc & 0xffc00000) == 0x6dc00000)
                                            return OP_ldp;
                                        if ((enc & 0xffc00000) == 0xadc00000)
                                            return OP_ldp;
                                    } else {
                                        if ((enc & 0x7f000000) == 0x35000000)
                                            return OP_cbnz;
                                        if ((enc & 0xffc00000) == 0x3dc00000)
                                            return OP_ldr;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        } else {
            if ((enc >> 10 & 1) == 0) {
                if ((enc >> 28 & 1) == 0) {
                    if ((enc >> 30 & 1) == 0) {
                        if ((enc >> 12 & 1) == 0) {
                            if ((enc >> 13 & 1) == 0) {
                                if ((enc >> 14 & 1) == 0) {
                                    if ((enc >> 15 & 1) == 0) {
                                        if ((enc & 0xff20fc00) == 0x0e200000)
                                            return OP_saddl;
                                        if ((enc & 0xff20fc00) == 0x2e200000)
                                            return OP_uaddl;
                                    } else {
                                        if ((enc & 0xff20fc00) == 0x0e208000)
                                            return OP_smlal;
                                        if ((enc & 0xff20fc00) == 0x2e208000)
                                            return OP_umlal;
                                    }
                                } else {
                                    if ((enc >> 15 & 1) == 0) {
                                        if ((enc & 0xff20fc00) == 0x0e204000)
                                            return OP_addhn;
                                        if ((enc & 0xff20fc00) == 0x2e204000)
                                            return OP_raddhn;
                                    } else {
                                        if ((enc & 0xff20fc00) == 0x0e20c000)
                                            return OP_smull;
                                        if ((enc & 0xff20fc00) == 0x2e20c000)
                                            return OP_umull;
                                    }
                                }
                            } else {
                                if ((enc >> 14 & 1) == 0) {
                                    if ((enc >> 15 & 1) == 0) {
                                        if ((enc & 0xff20fc00) == 0x0e202000)
                                            return OP_ssubl;
                                        if ((enc & 0xff20fc00) == 0x2e202000)
                                            return OP_usubl;
                                    } else {
                                        if ((enc & 0xff20fc00) == 0x0e20a000)
                                            return OP_smlsl;
                                        if ((enc & 0xff20fc00) == 0x2e20a000)
                                            return OP_umlsl;
                                    }
                                } else {
                                    if ((enc & 0xff20fc00) == 0x0e20e000)
                                        return OP_pmull;
                                    if ((enc & 0xff20fc00) == 0x2e206000)
                                        return OP_rsubhn;
                                    if ((enc & 0xff20fc00) == 0x0e206000)
                                        return OP_subhn;
                                }
                            }
                        } else {
                            if ((enc >> 13 & 1) == 0) {
                                if ((enc >> 14 & 1) == 0) {
                                    if ((enc >> 15 & 1) == 0) {
                                        if ((enc & 0xbf80f400) == 0x0f801000)
                                            return OP_fmla;
                                        if ((enc & 0xff20fc00) == 0x0e201000)
                                            return OP_saddw;
                                        if ((enc & 0xff20fc00) == 0x2e201000)
                                            return OP_uaddw;
                                    } else {
                                        if ((enc & 0xff20fc00) == 0x0e209000)
                                            return OP_sqdmlal;
                                    }
                                } else {
                                    if ((enc & 0xff20fc00) == 0x0e205000)
                                        return OP_sabal;
                                    if ((enc & 0xff20fc00) == 0x0e20d000)
                                        return OP_sqdmull;
                                    if ((enc & 0xff20fc00) == 0x2e205000)
                                        return OP_uabal;
                                }
                            } else {
                                if ((enc >> 14 & 1) == 0) {
                                    if ((enc & 0xff20fc00) == 0x0e20b000)
                                        return OP_sqdmlsl;
                                    if ((enc & 0xff20fc00) == 0x0e203000)
                                        return OP_ssubw;
                                    if ((enc & 0xff20fc00) == 0x2e203000)
                                        return OP_usubw;
                                } else {
                                    if ((enc & 0xff20fc00) == 0x0e207000)
                                        return OP_sabdl;
                                    if ((enc & 0xff20fc00) == 0x2e207000)
                                        return OP_uabdl;
                                }
                            }
                        }
                    } else {
                        if ((enc >> 12 & 1) == 0) {
                            if ((enc >> 13 & 1) == 0) {
                                if ((enc >> 14 & 1) == 0) {
                                    if ((enc >> 15 & 1) == 0) {
                                        if ((enc & 0xff20fc00) == 0x4e200000)
                                            return OP_saddl2;
                                        if ((enc & 0xff20fc00) == 0x6e200000)
                                            return OP_uaddl2;
                                    } else {
                                        if ((enc & 0xff20fc00) == 0x4e208000)
                                            return OP_smlal2;
                                        if ((enc & 0xff20fc00) == 0x6e208000)
                                            return OP_umlal2;
                                    }
                                } else {
                                    if ((enc >> 15 & 1) == 0) {
                                        if ((enc & 0xff20fc00) == 0x4e204000)
                                            return OP_addhn2;
                                        if ((enc & 0xff20fc00) == 0x6e204000)
                                            return OP_raddhn2;
                                    } else {
                                        if ((enc & 0xff20fc00) == 0x4e20c000)
                                            return OP_smull2;
                                        if ((enc & 0xff20fc00) == 0x6e20c000)
                                            return OP_umull2;
                                    }
                                }
                            } else {
                                if ((enc >> 14 & 1) == 0) {
                                    if ((enc >> 15 & 1) == 0) {
                                        if ((enc & 0xff20fc00) == 0x4e202000)
                                            return OP_ssubl2;
                                        if ((enc & 0xff20fc00) == 0x6e202000)
                                            return OP_usubl2;
                                    } else {
                                        if ((enc & 0xff20fc00) == 0x4e20a000)
                                            return OP_smlsl2;
                                        if ((enc & 0xff20fc00) == 0x6e20a000)
                                            return OP_umlsl2;
                                    }
                                } else {
                                    if ((enc & 0xff20fc00) == 0x4e20e000)
                                        return OP_pmull2;
                                    if ((enc & 0xff20fc00) == 0x6e206000)
                                        return OP_rsubhn2;
                                    if ((enc & 0xff20fc00) == 0x4e206000)
                                        return OP_subhn2;
                                }
                            }
                        } else {
                            if ((enc >> 13 & 1) == 0) {
                                if ((enc >> 14 & 1) == 0) {
                                    if ((enc >> 15 & 1) == 0) {
                                        if ((enc & 0xbf80f400) == 0x0f801000)
                                            return OP_fmla;
                                        if ((enc & 0xff20fc00) == 0x4e201000)
                                            return OP_saddw2;
                                        if ((enc & 0xff20fc00) == 0x6e201000)
                                            return OP_uaddw2;
                                    } else {
                                        if ((enc & 0xff20fc00) == 0x4e209000)
                                            return OP_sqdmlal2;
                                    }
                                } else {
                                    if ((enc & 0xff20fc00) == 0x4e205000)
                                        return OP_sabal2;
                                    if ((enc & 0xff20fc00) == 0x4e20d000)
                                        return OP_sqdmull2;
                                    if ((enc & 0xff20fc00) == 0x6e205000)
                                        return OP_uabal2;
                                }
                            } else {
                                if ((enc >> 14 & 1) == 0) {
                                    if ((enc & 0xff20fc00) == 0x4e20b000)
                                        return OP_sqdmlsl2;
                                    if ((enc & 0xff20fc00) == 0x4e203000)
                                        return OP_ssubw2;
                                    if ((enc & 0xff20fc00) == 0x6e203000)
                                        return OP_usubw2;
                                } else {
                                    if ((enc & 0xff20fc00) == 0x4e207000)
                                        return OP_sabdl2;
                                    if ((enc & 0xff20fc00) == 0x6e207000)
                                        return OP_uabdl2;
                                }
                            }
                        }
                    }
                } else {
                    if ((enc >> 14 & 1) == 0) {
                        if ((enc >> 27 & 1) == 0) {
                            if ((enc >> 30 & 1) == 0) {
                                if ((enc >> 29 & 1) == 0) {
                                    if ((enc & 0xfc000000) == 0x14000000)
                                        return OP_b;
                                    if ((enc & 0xfc000000) == 0x94000000)
                                        return OP_bl;
                                } else {
                                    if ((enc & 0x7f000000) == 0x37000000)
                                        return OP_tbnz;
                                    if ((enc & 0x7f000000) == 0x36000000)
                                        return OP_tbz;
                                }
                            } else {
                                if ((enc & 0xfffffc1f) == 0xd63f0000)
                                    return OP_blr;
                                if ((enc & 0xfffffc1f) == 0xd61f0000)
                                    return OP_br;
                                if ((enc & 0xfffffc1f) == 0xd65f0000)
                                    return OP_ret;
                            }
                        } else {
                            if ((enc >> 11 & 1) == 0) {
                                if ((enc >> 23 & 1) == 0) {
                                    if ((enc >> 24 & 1) == 0) {
                                        if ((enc >> 12 & 1) == 0) {
                                            if ((enc & 0xfffffc00) == 0x1e270000)
                                                return OP_fmov;
                                            if ((enc & 0xfffffc00) == 0x9e670000)
                                                return OP_fmov;
                                        } else {
                                            if ((enc & 0xffe01fe0) == 0x1e201000)
                                                return OP_fmov;
                                            if ((enc & 0xffe01fe0) == 0x1e601000)
                                                return OP_fmov;
                                        }
                                    } else {
                                        if ((enc >> 15 & 1) == 0) {
                                            if ((enc & 0xff208000) == 0x1f000000)
                                                return OP_fmadd;
                                            if ((enc & 0xff208000) == 0x1f200000)
                                                return OP_fnmadd;
                                        } else {
                                            if ((enc & 0xff208000) == 0x1f008000)
                                                return OP_fmsub;
                                            if ((enc & 0xff208000) == 0x1f208000)
                                                return OP_fnmsub;
                                        }
                                    }
                                } else {
                                    if ((enc >> 24 & 1) == 0) {
                                        if ((enc >> 31 & 1) == 0) {
                                            if ((enc & 0xffe01fe0) == 0x1ee01000)
                                                return OP_fmov;
                                            if ((enc & 0xfffffc00) == 0x1ee70000)
                                                return OP_fmov;
                                        } else {
                                            if ((enc & 0xfffffc00) == 0x9eaf0000)
                                                return OP_fmov;
                                            if ((enc & 0xfffffc00) == 0x9ee70000)
                                                return OP_fmov;
                                        }
                                    } else {
                                        if ((enc >> 15 & 1) == 0) {
                                            if ((enc & 0xff208000) == 0x1f000000)
                                                return OP_fmadd;
                                            if ((enc & 0xff208000) == 0x1f200000)
                                                return OP_fnmadd;
                                        } else {
                                            if ((enc & 0xff208000) == 0x1f008000)
                                                return OP_fmsub;
                                            if ((enc & 0xff208000) == 0x1f208000)
                                                return OP_fnmsub;
                                        }
                                    }
                                }
                            } else {
                                if ((enc >> 24 & 1) == 0) {
                                    if ((enc >> 12 & 1) == 0) {
                                        if ((enc & 0xff20fc00) == 0x1e202800)
                                            return OP_fadd;
                                        if ((enc & 0xff20fc00) == 0x1e200800)
                                            return OP_fmul;
                                        if ((enc & 0xff20fc00) == 0x1e208800)
                                            return OP_fnmul;
                                    } else {
                                        if ((enc & 0xff20fc00) == 0x1e201800)
                                            return OP_fdiv;
                                        if ((enc & 0xff20fc00) == 0x1e203800)
                                            return OP_fsub;
                                    }
                                } else {
                                    if ((enc >> 15 & 1) == 0) {
                                        if ((enc & 0xff208000) == 0x1f000000)
                                            return OP_fmadd;
                                        if ((enc & 0xff208000) == 0x1f200000)
                                            return OP_fnmadd;
                                    } else {
                                        if ((enc & 0xff208000) == 0x1f008000)
                                            return OP_fmsub;
                                        if ((enc & 0xff208000) == 0x1f208000)
                                            return OP_fnmsub;
                                    }
                                }
                            }
                        }
                    } else {
                        if ((enc >> 15 & 1) == 0) {
                            if ((enc >> 12 & 1) == 0) {
                                if ((enc >> 17 & 1) == 0) {
                                    if ((enc >> 27 & 1) == 0) {
                                        if ((enc >> 29 & 1) == 0) {
                                            if ((enc & 0xfc000000) == 0x14000000)
                                                return OP_b;
                                            if ((enc & 0xfc000000) == 0x94000000)
                                                return OP_bl;
                                        } else {
                                            if ((enc & 0x7f000000) == 0x37000000)
                                                return OP_tbnz;
                                            if ((enc & 0x7f000000) == 0x36000000)
                                                return OP_tbz;
                                        }
                                    } else {
                                        if ((enc >> 11 & 1) == 0) {
                                            if ((enc >> 16 & 1) == 0) {
                                                if ((enc >> 24 & 1) == 0) {
                                                    if ((enc & 0xff3ffc00) == 0x1e204000)
                                                        return OP_fmov;
                                                    if ((enc & 0xff3ffc00) == 0x1e244000)
                                                        return OP_frintn;
                                                } else {
                                                    if ((enc & 0xff208000) == 0x1f000000)
                                                        return OP_fmadd;
                                                    if ((enc & 0xff208000) == 0x1f200000)
                                                        return OP_fnmadd;
                                                }
                                            } else {
                                                if ((enc >> 24 & 1) == 0) {
                                                    if ((enc & 0xff3ffc00) == 0x1e214000)
                                                        return OP_fneg;
                                                    if ((enc & 0xff3ffc00) == 0x1e254000)
                                                        return OP_frintm;
                                                } else {
                                                    if ((enc & 0xff208000) == 0x1f000000)
                                                        return OP_fmadd;
                                                    if ((enc & 0xff208000) == 0x1f200000)
                                                        return OP_fnmadd;
                                                }
                                            }
                                        } else {
                                            if ((enc >> 24 & 1) == 0) {
                                                if ((enc & 0xff20fc00) == 0x1e204800)
                                                    return OP_fmax;
                                                if ((enc & 0xff20fc00) == 0x1e206800)
                                                    return OP_fmaxnm;
                                            } else {
                                                if ((enc & 0xff208000) == 0x1f000000)
                                                    return OP_fmadd;
                                                if ((enc & 0xff208000) == 0x1f200000)
                                                    return OP_fnmadd;
                                            }
                                        }
                                    }
                                } else {
                                    if ((enc >> 27 & 1) == 0) {
                                        if ((enc >> 29 & 1) == 0) {
                                            if ((enc & 0xfc000000) == 0x14000000)
                                                return OP_b;
                                            if ((enc & 0xfc000000) == 0x94000000)
                                                return OP_bl;
                                        } else {
                                            if ((enc & 0x7f000000) == 0x37000000)
                                                return OP_tbnz;
                                            if ((enc & 0x7f000000) == 0x36000000)
                                                return OP_tbz;
                                        }
                                    } else {
                                        if ((enc >> 11 & 1) == 0) {
                                            if ((enc >> 18 & 1) == 0) {
                                                if ((enc >> 24 & 1) == 0) {
                                                    if ((enc & 0xfffffc00) == 0x1e624000)
                                                        return OP_fcvt;
                                                    if ((enc & 0xfffffc00) == 0x1ee24000)
                                                        return OP_fcvt;
                                                } else {
                                                    if ((enc & 0xff208000) == 0x1f000000)
                                                        return OP_fmadd;
                                                    if ((enc & 0xff208000) == 0x1f200000)
                                                        return OP_fnmadd;
                                                }
                                            } else {
                                                if ((enc >> 24 & 1) == 0) {
                                                    if ((enc & 0xff3ffc00) == 0x1e264000)
                                                        return OP_frinta;
                                                    if ((enc & 0xff3ffc00) == 0x1e274000)
                                                        return OP_frintx;
                                                } else {
                                                    if ((enc & 0xff208000) == 0x1f000000)
                                                        return OP_fmadd;
                                                    if ((enc & 0xff208000) == 0x1f200000)
                                                        return OP_fnmadd;
                                                }
                                            }
                                        } else {
                                            if ((enc >> 24 & 1) == 0) {
                                                if ((enc & 0xff20fc00) == 0x1e204800)
                                                    return OP_fmax;
                                                if ((enc & 0xff20fc00) == 0x1e206800)
                                                    return OP_fmaxnm;
                                            } else {
                                                if ((enc & 0xff208000) == 0x1f000000)
                                                    return OP_fmadd;
                                                if ((enc & 0xff208000) == 0x1f200000)
                                                    return OP_fnmadd;
                                            }
                                        }
                                    }
                                }
                            } else {
                                if ((enc >> 27 & 1) == 0) {
                                    if ((enc >> 29 & 1) == 0) {
                                        if ((enc & 0xfc000000) == 0x14000000)
                                            return OP_b;
                                        if ((enc & 0xfc000000) == 0x94000000)
                                            return OP_bl;
                                    } else {
                                        if ((enc & 0x7f000000) == 0x37000000)
                                            return OP_tbnz;
                                        if ((enc & 0x7f000000) == 0x36000000)
                                            return OP_tbz;
                                    }
                                } else {
                                    if ((enc >> 11 & 1) == 0) {
                                        if ((enc >> 24 & 1) == 0) {
                                            if ((enc & 0xffe01fe0) == 0x1e201000)
                                                return OP_fmov;
                                            if ((enc & 0xffe01fe0) == 0x1e601000)
                                                return OP_fmov;
                                            if ((enc & 0xffe01fe0) == 0x1ee01000)
                                                return OP_fmov;
                                        } else {
                                            if ((enc & 0xff208000) == 0x1f000000)
                                                return OP_fmadd;
                                            if ((enc & 0xff208000) == 0x1f200000)
                                                return OP_fnmadd;
                                        }
                                    } else {
                                        if ((enc >> 24 & 1) == 0) {
                                            if ((enc & 0xff20fc00) == 0x1e205800)
                                                return OP_fmin;
                                            if ((enc & 0xff20fc00) == 0x1e207800)
                                                return OP_fminnm;
                                        } else {
                                            if ((enc & 0xff208000) == 0x1f000000)
                                                return OP_fmadd;
                                            if ((enc & 0xff208000) == 0x1f200000)
                                                return OP_fnmadd;
                                        }
                                    }
                                }
                            }
                        } else {
                            if ((enc >> 16 & 1) == 0) {
                                if ((enc >> 27 & 1) == 0) {
                                    if ((enc >> 29 & 1) == 0) {
                                        if ((enc & 0xfc000000) == 0x14000000)
                                            return OP_b;
                                        if ((enc & 0xfc000000) == 0x94000000)
                                            return OP_bl;
                                    } else {
                                        if ((enc & 0x7f000000) == 0x37000000)
                                            return OP_tbnz;
                                        if ((enc & 0x7f000000) == 0x36000000)
                                            return OP_tbz;
                                    }
                                } else {
                                    if ((enc >> 12 & 1) == 0) {
                                        if ((enc >> 17 & 1) == 0) {
                                            if ((enc >> 24 & 1) == 0) {
                                                if ((enc & 0xff3ffc00) == 0x1e20c000)
                                                    return OP_fabs;
                                                if ((enc & 0xff3ffc00) == 0x1e24c000)
                                                    return OP_frintp;
                                            } else {
                                                if ((enc & 0xff208000) == 0x1f008000)
                                                    return OP_fmsub;
                                                if ((enc & 0xff208000) == 0x1f208000)
                                                    return OP_fnmsub;
                                            }
                                        } else {
                                            if ((enc >> 24 & 1) == 0) {
                                                if ((enc & 0xfffffc00) == 0x1e22c000)
                                                    return OP_fcvt;
                                                if ((enc & 0xfffffc00) == 0x1ee2c000)
                                                    return OP_fcvt;
                                            } else {
                                                if ((enc & 0xff208000) == 0x1f008000)
                                                    return OP_fmsub;
                                                if ((enc & 0xff208000) == 0x1f208000)
                                                    return OP_fnmsub;
                                            }
                                        }
                                    } else {
                                        if ((enc >> 24 & 1) == 0) {
                                            if ((enc & 0xffe01fe0) == 0x1e201000)
                                                return OP_fmov;
                                            if ((enc & 0xffe01fe0) == 0x1e601000)
                                                return OP_fmov;
                                            if ((enc & 0xffe01fe0) == 0x1ee01000)
                                                return OP_fmov;
                                        } else {
                                            if ((enc & 0xff208000) == 0x1f008000)
                                                return OP_fmsub;
                                            if ((enc & 0xff208000) == 0x1f208000)
                                                return OP_fnmsub;
                                        }
                                    }
                                }
                            } else {
                                if ((enc >> 27 & 1) == 0) {
                                    if ((enc >> 29 & 1) == 0) {
                                        if ((enc & 0xfc000000) == 0x14000000)
                                            return OP_b;
                                        if ((enc & 0xfc000000) == 0x94000000)
                                            return OP_bl;
                                    } else {
                                        if ((enc & 0x7f000000) == 0x37000000)
                                            return OP_tbnz;
                                        if ((enc & 0x7f000000) == 0x36000000)
                                            return OP_tbz;
                                    }
                                } else {
                                    if ((enc >> 12 & 1) == 0) {
                                        if ((enc >> 17 & 1) == 0) {
                                            if ((enc >> 24 & 1) == 0) {
                                                if ((enc & 0xff3ffc00) == 0x1e25c000)
                                                    return OP_frintz;
                                                if ((enc & 0xff3ffc00) == 0x1e21c000)
                                                    return OP_fsqrt;
                                            } else {
                                                if ((enc & 0xff208000) == 0x1f008000)
                                                    return OP_fmsub;
                                                if ((enc & 0xff208000) == 0x1f208000)
                                                    return OP_fnmsub;
                                            }
                                        } else {
                                            if ((enc >> 24 & 1) == 0) {
                                                if ((enc & 0xfffffc00) == 0x1e23c000)
                                                    return OP_fcvt;
                                                if ((enc & 0xfffffc00) == 0x1e63c000)
                                                    return OP_fcvt;
                                                if ((enc & 0xff3ffc00) == 0x1e27c000)
                                                    return OP_frinti;
                                            } else {
                                                if ((enc & 0xff208000) == 0x1f008000)
                                                    return OP_fmsub;
                                                if ((enc & 0xff208000) == 0x1f208000)
                                                    return OP_fnmsub;
                                            }
                                        }
                                    } else {
                                        if ((enc >> 24 & 1) == 0) {
                                            if ((enc & 0xffe01fe0) == 0x1e201000)
                                                return OP_fmov;
                                            if ((enc & 0xffe01fe0) == 0x1e601000)
                                                return OP_fmov;
                                            if ((enc & 0xffe01fe0) == 0x1ee01000)
                                                return OP_fmov;
                                        } else {
                                            if ((enc & 0xff208000) == 0x1f008000)
                                                return OP_fmsub;
                                            if ((enc & 0xff208000) == 0x1f208000)
                                                return OP_fnmsub;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            } else {
                if ((enc >> 29 & 1) == 0) {
                    if ((enc >> 11 & 1) == 0) {
                        if ((enc >> 15 & 1) == 0) {
                            if ((enc >> 21 & 1) == 0) {
                                if ((enc >> 12 & 1) == 0) {
                                    if ((enc >> 28 & 1) == 0) {
                                        if ((enc & 0xbfe0fc00) == 0x0e402400)
                                            return OP_fcmeq;
                                        if ((enc & 0xbfe0fc00) == 0x0e400400)
                                            return OP_fmaxnm;
                                        if ((enc & 0xbfe0fc00) == 0x0ec00400)
                                            return OP_fminnm;
                                    } else {
                                        if ((enc & 0xfc000000) == 0x14000000)
                                            return OP_b;
                                        if ((enc & 0xfc000000) == 0x94000000)
                                            return OP_bl;
                                        if ((enc & 0xff208000) == 0x1f000000)
                                            return OP_fmadd;
                                    }
                                } else {
                                    if ((enc >> 28 & 1) == 0) {
                                        if ((enc >> 13 & 1) == 0) {
                                            if ((enc & 0xbfe0fc00) == 0x0e401400)
                                                return OP_fadd;
                                            if ((enc & 0xbfe0fc00) == 0x0ec01400)
                                                return OP_fsub;
                                        } else {
                                            if ((enc & 0xbfe0fc00) == 0x0e403400)
                                                return OP_fmax;
                                            if ((enc & 0xbfe0fc00) == 0x0ec03400)
                                                return OP_fmin;
                                        }
                                    } else {
                                        if ((enc & 0xfc000000) == 0x14000000)
                                            return OP_b;
                                        if ((enc & 0xfc000000) == 0x94000000)
                                            return OP_bl;
                                        if ((enc & 0xff208000) == 0x1f000000)
                                            return OP_fmadd;
                                    }
                                }
                            } else {
                                if ((enc >> 12 & 1) == 0) {
                                    if ((enc >> 28 & 1) == 0) {
                                        if ((enc >> 13 & 1) == 0) {
                                            if ((enc & 0xbf20fc00) == 0x0e200400)
                                                return OP_shadd;
                                            if ((enc & 0xbf20fc00) == 0x0e204400)
                                                return OP_sshl;
                                        } else {
                                            if ((enc & 0xbf20fc00) == 0x0e202400)
                                                return OP_shsub;
                                            if ((enc & 0xbf20fc00) == 0x0e206400)
                                                return OP_smax;
                                        }
                                    } else {
                                        if ((enc & 0xfc000000) == 0x14000000)
                                            return OP_b;
                                        if ((enc & 0xfc000000) == 0x94000000)
                                            return OP_bl;
                                        if ((enc & 0xff208000) == 0x1f200000)
                                            return OP_fnmadd;
                                    }
                                } else {
                                    if ((enc >> 28 & 1) == 0) {
                                        if ((enc >> 13 & 1) == 0) {
                                            if ((enc & 0xbf20fc00) == 0x0e201400)
                                                return OP_srhadd;
                                            if ((enc & 0xbf20fc00) == 0x0e205400)
                                                return OP_srshl;
                                        } else {
                                            if ((enc & 0xbf20fc00) == 0x0e203400)
                                                return OP_cmgt;
                                            if ((enc & 0xbf20fc00) == 0x0e207400)
                                                return OP_sabd;
                                        }
                                    } else {
                                        if ((enc & 0xfc000000) == 0x14000000)
                                            return OP_b;
                                        if ((enc & 0xfc000000) == 0x94000000)
                                            return OP_bl;
                                        if ((enc & 0xff208000) == 0x1f200000)
                                            return OP_fnmadd;
                                    }
                                }
                            }
                        } else {
                            if ((enc >> 12 & 1) == 0) {
                                if ((enc >> 28 & 1) == 0) {
                                    if ((enc >> 13 & 1) == 0) {
                                        if ((enc & 0xbf20fc00) == 0x0e208400)
                                            return OP_add;
                                        if ((enc & 0xbfa0fc00) == 0x0e20c400)
                                            return OP_fmaxnm;
                                        if ((enc & 0xbfa0fc00) == 0x0ea0c400)
                                            return OP_fminnm;
                                    } else {
                                        if ((enc & 0xbfa0fc00) == 0x0e20e400)
                                            return OP_fcmeq;
                                        if ((enc & 0xbf20fc00) == 0x0e20a400)
                                            return OP_smaxp;
                                    }
                                } else {
                                    if ((enc >> 27 & 1) == 0) {
                                        if ((enc & 0xfc000000) == 0x14000000)
                                            return OP_b;
                                        if ((enc & 0xfc000000) == 0x94000000)
                                            return OP_bl;
                                    } else {
                                        if ((enc & 0xff208000) == 0x1f008000)
                                            return OP_fmsub;
                                        if ((enc & 0xff208000) == 0x1f208000)
                                            return OP_fnmsub;
                                    }
                                }
                            } else {
                                if ((enc >> 28 & 1) == 0) {
                                    if ((enc >> 13 & 1) == 0) {
                                        if ((enc & 0xbfa0fc00) == 0x0e20d400)
                                            return OP_fadd;
                                        if ((enc & 0xbfa0fc00) == 0x0ea0d400)
                                            return OP_fsub;
                                        if ((enc & 0xbf20fc00) == 0x0e209400)
                                            return OP_mla;
                                    } else {
                                        if ((enc & 0xbfa0fc00) == 0x0e20f400)
                                            return OP_fmax;
                                        if ((enc & 0xbfa0fc00) == 0x0ea0f400)
                                            return OP_fmin;
                                        if ((enc & 0xbf20fc00) == 0x0e20b400)
                                            return OP_sqdmulh;
                                    }
                                } else {
                                    if ((enc >> 27 & 1) == 0) {
                                        if ((enc & 0xfc000000) == 0x14000000)
                                            return OP_b;
                                        if ((enc & 0xfc000000) == 0x94000000)
                                            return OP_bl;
                                    } else {
                                        if ((enc & 0xff208000) == 0x1f008000)
                                            return OP_fmsub;
                                        if ((enc & 0xff208000) == 0x1f208000)
                                            return OP_fnmsub;
                                    }
                                }
                            }
                        }
                    } else {
                        if ((enc >> 15 & 1) == 0) {
                            if ((enc >> 12 & 1) == 0) {
                                if ((enc >> 28 & 1) == 0) {
                                    if ((enc >> 13 & 1) == 0) {
                                        if ((enc >> 21 & 1) == 0) {
                                            if ((enc & 0xbfe0fc00) == 0x0e400c00)
                                                return OP_fmla;
                                            if ((enc & 0xbfe0fc00) == 0x0ec00c00)
                                                return OP_fmls;
                                        } else {
                                            if ((enc & 0xbf20fc00) == 0x0e200c00)
                                                return OP_sqadd;
                                            if ((enc & 0xbf20fc00) == 0x0e204c00)
                                                return OP_sqshl;
                                        }
                                    } else {
                                        if ((enc & 0xbf20fc00) == 0x0e206c00)
                                            return OP_smin;
                                        if ((enc & 0xbf20fc00) == 0x0e202c00)
                                            return OP_sqsub;
                                    }
                                } else {
                                    if ((enc >> 27 & 1) == 0) {
                                        if ((enc & 0xfc000000) == 0x14000000)
                                            return OP_b;
                                        if ((enc & 0xfc000000) == 0x94000000)
                                            return OP_bl;
                                    } else {
                                        if ((enc & 0xff208000) == 0x1f000000)
                                            return OP_fmadd;
                                        if ((enc & 0xff208000) == 0x1f200000)
                                            return OP_fnmadd;
                                    }
                                }
                            } else {
                                if ((enc >> 13 & 1) == 0) {
                                    if ((enc >> 28 & 1) == 0) {
                                        if ((enc >> 22 & 1) == 0) {
                                            if ((enc & 0xbfe0fc00) == 0x0e201c00)
                                                return OP_and;
                                            if ((enc & 0xbfe0fc00) == 0x0ea01c00)
                                                return OP_orr;
                                            if ((enc & 0xbf20fc00) == 0x0e205c00)
                                                return OP_sqrshl;
                                        } else {
                                            if ((enc >> 14 & 1) == 0) {
                                                if ((enc & 0xbfe0fc00) == 0x0e601c00)
                                                    return OP_bic;
                                                if ((enc & 0xbfe0fc00) == 0x0e401c00)
                                                    return OP_fmulx;
                                                if ((enc & 0xbfe0fc00) == 0x0ee01c00)
                                                    return OP_orn;
                                            } else {
                                                if ((enc & 0xbf20fc00) == 0x0e205c00)
                                                    return OP_sqrshl;
                                            }
                                        }
                                    } else {
                                        if ((enc >> 27 & 1) == 0) {
                                            if ((enc & 0xfc000000) == 0x14000000)
                                                return OP_b;
                                            if ((enc & 0xfc000000) == 0x94000000)
                                                return OP_bl;
                                        } else {
                                            if ((enc & 0xff208000) == 0x1f000000)
                                                return OP_fmadd;
                                            if ((enc & 0xff208000) == 0x1f200000)
                                                return OP_fnmadd;
                                        }
                                    }
                                } else {
                                    if ((enc >> 28 & 1) == 0) {
                                        if ((enc >> 21 & 1) == 0) {
                                            if ((enc & 0xbfe0fc00) == 0x0e403c00)
                                                return OP_frecps;
                                            if ((enc & 0xbfe0fc00) == 0x0ec03c00)
                                                return OP_frsqrts;
                                        } else {
                                            if ((enc & 0xbf20fc00) == 0x0e203c00)
                                                return OP_cmge;
                                            if ((enc & 0xbf20fc00) == 0x0e207c00)
                                                return OP_saba;
                                        }
                                    } else {
                                        if ((enc >> 27 & 1) == 0) {
                                            if ((enc & 0xfc000000) == 0x14000000)
                                                return OP_b;
                                            if ((enc & 0xfc000000) == 0x94000000)
                                                return OP_bl;
                                        } else {
                                            if ((enc & 0xff208000) == 0x1f000000)
                                                return OP_fmadd;
                                            if ((enc & 0xff208000) == 0x1f200000)
                                                return OP_fnmadd;
                                        }
                                    }
                                }
                            }
                        } else {
                            if ((enc >> 12 & 1) == 0) {
                                if ((enc >> 28 & 1) == 0) {
                                    if ((enc >> 13 & 1) == 0) {
                                        if ((enc & 0xbf20fc00) == 0x0e208c00)
                                            return OP_cmtst;
                                        if ((enc & 0xbfa0fc00) == 0x0e20cc00)
                                            return OP_fmla;
                                        if ((enc & 0xbfa0fc00) == 0x0ea0cc00)
                                            return OP_fmls;
                                    } else {
                                        if ((enc & 0xbfe0fc00) == 0x0e20ec00)
                                            return OP_fmlal;
                                        if ((enc & 0xbfe0fc00) == 0x0ea0ec00)
                                            return OP_fmlsl;
                                        if ((enc & 0xbf20fc00) == 0x0e20ac00)
                                            return OP_sminp;
                                    }
                                } else {
                                    if ((enc >> 27 & 1) == 0) {
                                        if ((enc & 0xfc000000) == 0x14000000)
                                            return OP_b;
                                        if ((enc & 0xfc000000) == 0x94000000)
                                            return OP_bl;
                                    } else {
                                        if ((enc & 0xff208000) == 0x1f008000)
                                            return OP_fmsub;
                                        if ((enc & 0xff208000) == 0x1f208000)
                                            return OP_fnmsub;
                                    }
                                }
                            } else {
                                if ((enc >> 28 & 1) == 0) {
                                    if ((enc >> 13 & 1) == 0) {
                                        if ((enc & 0xbfa0fc00) == 0x0e20dc00)
                                            return OP_fmulx;
                                        if ((enc & 0xbf20fc00) == 0x0e209c00)
                                            return OP_mul;
                                    } else {
                                        if ((enc >> 14 & 1) == 0) {
                                            if ((enc & 0xbf20fc00) == 0x0e20bc00)
                                                return OP_addp;
                                        } else {
                                            if ((enc & 0xbff8fc00) == 0x0f00fc00)
                                                return OP_fmov;
                                            if ((enc & 0xbfa0fc00) == 0x0e20fc00)
                                                return OP_frecps;
                                            if ((enc & 0xbfa0fc00) == 0x0ea0fc00)
                                                return OP_frsqrts;
                                        }
                                    }
                                } else {
                                    if ((enc >> 27 & 1) == 0) {
                                        if ((enc & 0xfc000000) == 0x14000000)
                                            return OP_b;
                                        if ((enc & 0xfc000000) == 0x94000000)
                                            return OP_bl;
                                    } else {
                                        if ((enc & 0xff208000) == 0x1f008000)
                                            return OP_fmsub;
                                        if ((enc & 0xff208000) == 0x1f208000)
                                            return OP_fnmsub;
                                    }
                                }
                            }
                        }
                    }
                } else {
                    if ((enc >> 12 & 1) == 0) {
                        if ((enc >> 11 & 1) == 0) {
                            if ((enc >> 13 & 1) == 0) {
                                if ((enc >> 14 & 1) == 0) {
                                    if ((enc >> 21 & 1) == 0) {
                                        if ((enc >> 27 & 1) == 0) {
                                            if ((enc & 0x7f000000) == 0x37000000)
                                                return OP_tbnz;
                                            if ((enc & 0x7f000000) == 0x36000000)
                                                return OP_tbz;
                                        } else {
                                            if ((enc & 0xbfe0fc00) == 0x2e400400)
                                                return OP_fmaxnmp;
                                            if ((enc & 0xbfe0fc00) == 0x2ec00400)
                                                return OP_fminnmp;
                                        }
                                    } else {
                                        if ((enc >> 27 & 1) == 0) {
                                            if ((enc & 0x7f000000) == 0x37000000)
                                                return OP_tbnz;
                                            if ((enc & 0x7f000000) == 0x36000000)
                                                return OP_tbz;
                                        } else {
                                            if ((enc & 0xbf20fc00) == 0x2e208400)
                                                return OP_sub;
                                            if ((enc & 0xbf20fc00) == 0x2e200400)
                                                return OP_uhadd;
                                        }
                                    }
                                } else {
                                    if ((enc >> 27 & 1) == 0) {
                                        if ((enc & 0x7f000000) == 0x37000000)
                                            return OP_tbnz;
                                        if ((enc & 0x7f000000) == 0x36000000)
                                            return OP_tbz;
                                    } else {
                                        if ((enc & 0xbfa0fc00) == 0x2e20c400)
                                            return OP_fmaxnmp;
                                        if ((enc & 0xbfa0fc00) == 0x2ea0c400)
                                            return OP_fminnmp;
                                        if ((enc & 0xbf20fc00) == 0x2e204400)
                                            return OP_ushl;
                                    }
                                }
                            } else {
                                if ((enc >> 14 & 1) == 0) {
                                    if ((enc >> 21 & 1) == 0) {
                                        if ((enc >> 27 & 1) == 0) {
                                            if ((enc & 0x7f000000) == 0x37000000)
                                                return OP_tbnz;
                                            if ((enc & 0x7f000000) == 0x36000000)
                                                return OP_tbz;
                                        } else {
                                            if ((enc & 0xbfe0fc00) == 0x2e402400)
                                                return OP_fcmge;
                                            if ((enc & 0xbfe0fc00) == 0x2ec02400)
                                                return OP_fcmgt;
                                        }
                                    } else {
                                        if ((enc >> 27 & 1) == 0) {
                                            if ((enc & 0x7f000000) == 0x37000000)
                                                return OP_tbnz;
                                            if ((enc & 0x7f000000) == 0x36000000)
                                                return OP_tbz;
                                        } else {
                                            if ((enc & 0xbf20fc00) == 0x2e202400)
                                                return OP_uhsub;
                                            if ((enc & 0xbf20fc00) == 0x2e20a400)
                                                return OP_umaxp;
                                        }
                                    }
                                } else {
                                    if ((enc >> 27 & 1) == 0) {
                                        if ((enc & 0x7f000000) == 0x37000000)
                                            return OP_tbnz;
                                        if ((enc & 0x7f000000) == 0x36000000)
                                            return OP_tbz;
                                    } else {
                                        if ((enc & 0xbfa0fc00) == 0x2e20e400)
                                            return OP_fcmge;
                                        if ((enc & 0xbfa0fc00) == 0x2ea0e400)
                                            return OP_fcmgt;
                                        if ((enc & 0xbf20fc00) == 0x2e206400)
                                            return OP_umax;
                                    }
                                }
                            }
                        } else {
                            if ((enc >> 14 & 1) == 0) {
                                if ((enc >> 13 & 1) == 0) {
                                    if ((enc >> 27 & 1) == 0) {
                                        if ((enc & 0x7f000000) == 0x37000000)
                                            return OP_tbnz;
                                        if ((enc & 0x7f000000) == 0x36000000)
                                            return OP_tbz;
                                    } else {
                                        if ((enc & 0xbf20fc00) == 0x2e208c00)
                                            return OP_cmeq;
                                        if ((enc & 0xbf20fc00) == 0x2e200c00)
                                            return OP_uqadd;
                                    }
                                } else {
                                    if ((enc >> 21 & 1) == 0) {
                                        if ((enc >> 27 & 1) == 0) {
                                            if ((enc & 0x7f000000) == 0x37000000)
                                                return OP_tbnz;
                                            if ((enc & 0x7f000000) == 0x36000000)
                                                return OP_tbz;
                                        } else {
                                            if ((enc & 0xbfe0fc00) == 0x2e402c00)
                                                return OP_facge;
                                            if ((enc & 0xbfe0fc00) == 0x2ec02c00)
                                                return OP_facgt;
                                        }
                                    } else {
                                        if ((enc >> 27 & 1) == 0) {
                                            if ((enc & 0x7f000000) == 0x37000000)
                                                return OP_tbnz;
                                            if ((enc & 0x7f000000) == 0x36000000)
                                                return OP_tbz;
                                        } else {
                                            if ((enc & 0xbf20fc00) == 0x2e20ac00)
                                                return OP_uminp;
                                            if ((enc & 0xbf20fc00) == 0x2e202c00)
                                                return OP_uqsub;
                                        }
                                    }
                                }
                            } else {
                                if ((enc >> 13 & 1) == 0) {
                                    if ((enc >> 27 & 1) == 0) {
                                        if ((enc & 0x7f000000) == 0x37000000)
                                            return OP_tbnz;
                                        if ((enc & 0x7f000000) == 0x36000000)
                                            return OP_tbz;
                                    } else {
                                        if ((enc & 0xbfe0fc00) == 0x2e20cc00)
                                            return OP_fmlal2;
                                        if ((enc & 0xbfe0fc00) == 0x2ea0cc00)
                                            return OP_fmlsl2;
                                        if ((enc & 0xbf20fc00) == 0x2e204c00)
                                            return OP_uqshl;
                                    }
                                } else {
                                    if ((enc >> 27 & 1) == 0) {
                                        if ((enc & 0x7f000000) == 0x37000000)
                                            return OP_tbnz;
                                        if ((enc & 0x7f000000) == 0x36000000)
                                            return OP_tbz;
                                    } else {
                                        if ((enc & 0xbfa0fc00) == 0x2e20ec00)
                                            return OP_facge;
                                        if ((enc & 0xbfa0fc00) == 0x2ea0ec00)
                                            return OP_facgt;
                                        if ((enc & 0xbf20fc00) == 0x2e206c00)
                                            return OP_umin;
                                    }
                                }
                            }
                        }
                    } else {
                        if ((enc >> 11 & 1) == 0) {
                            if ((enc >> 13 & 1) == 0) {
                                if ((enc >> 14 & 1) == 0) {
                                    if ((enc >> 21 & 1) == 0) {
                                        if ((enc >> 27 & 1) == 0) {
                                            if ((enc & 0x7f000000) == 0x37000000)
                                                return OP_tbnz;
                                            if ((enc & 0x7f000000) == 0x36000000)
                                                return OP_tbz;
                                        } else {
                                            if ((enc & 0xbfe0fc00) == 0x2ec01400)
                                                return OP_fabd;
                                            if ((enc & 0xbfe0fc00) == 0x2e401400)
                                                return OP_faddp;
                                        }
                                    } else {
                                        if ((enc >> 27 & 1) == 0) {
                                            if ((enc & 0x7f000000) == 0x37000000)
                                                return OP_tbnz;
                                            if ((enc & 0x7f000000) == 0x36000000)
                                                return OP_tbz;
                                        } else {
                                            if ((enc & 0xbf20fc00) == 0x2e209400)
                                                return OP_mls;
                                            if ((enc & 0xbf20fc00) == 0x2e201400)
                                                return OP_urhadd;
                                        }
                                    }
                                } else {
                                    if ((enc >> 27 & 1) == 0) {
                                        if ((enc & 0x7f000000) == 0x37000000)
                                            return OP_tbnz;
                                        if ((enc & 0x7f000000) == 0x36000000)
                                            return OP_tbz;
                                    } else {
                                        if ((enc & 0xbfa0fc00) == 0x2ea0d400)
                                            return OP_fabd;
                                        if ((enc & 0xbfa0fc00) == 0x2e20d400)
                                            return OP_faddp;
                                        if ((enc & 0xbf20fc00) == 0x2e205400)
                                            return OP_urshl;
                                    }
                                }
                            } else {
                                if ((enc >> 14 & 1) == 0) {
                                    if ((enc >> 21 & 1) == 0) {
                                        if ((enc >> 27 & 1) == 0) {
                                            if ((enc & 0x7f000000) == 0x37000000)
                                                return OP_tbnz;
                                            if ((enc & 0x7f000000) == 0x36000000)
                                                return OP_tbz;
                                        } else {
                                            if ((enc & 0xbfe0fc00) == 0x2e403400)
                                                return OP_fmaxp;
                                            if ((enc & 0xbfe0fc00) == 0x2ec03400)
                                                return OP_fminp;
                                        }
                                    } else {
                                        if ((enc >> 27 & 1) == 0) {
                                            if ((enc & 0x7f000000) == 0x37000000)
                                                return OP_tbnz;
                                            if ((enc & 0x7f000000) == 0x36000000)
                                                return OP_tbz;
                                        } else {
                                            if ((enc & 0xbf20fc00) == 0x2e203400)
                                                return OP_cmhi;
                                            if ((enc & 0xbf20fc00) == 0x2e20b400)
                                                return OP_sqrdmulh;
                                        }
                                    }
                                } else {
                                    if ((enc >> 27 & 1) == 0) {
                                        if ((enc & 0x7f000000) == 0x37000000)
                                            return OP_tbnz;
                                        if ((enc & 0x7f000000) == 0x36000000)
                                            return OP_tbz;
                                    } else {
                                        if ((enc & 0xbfa0fc00) == 0x2e20f400)
                                            return OP_fmaxp;
                                        if ((enc & 0xbfa0fc00) == 0x2ea0f400)
                                            return OP_fminp;
                                        if ((enc & 0xbf20fc00) == 0x2e207400)
                                            return OP_uabd;
                                    }
                                }
                            }
                        } else {
                            if ((enc >> 13 & 1) == 0) {
                                if ((enc >> 14 & 1) == 0) {
                                    if ((enc >> 22 & 1) == 0) {
                                        if ((enc >> 27 & 1) == 0) {
                                            if ((enc & 0x7f000000) == 0x37000000)
                                                return OP_tbnz;
                                            if ((enc & 0x7f000000) == 0x36000000)
                                                return OP_tbz;
                                        } else {
                                            if ((enc & 0xbfe0fc00) == 0x2ea01c00)
                                                return OP_bit;
                                            if ((enc & 0xbfe0fc00) == 0x2e201c00)
                                                return OP_eor;
                                            if ((enc & 0xbf20fc00) == 0x2e209c00)
                                                return OP_pmul;
                                        }
                                    } else {
                                        if ((enc >> 27 & 1) == 0) {
                                            if ((enc & 0x7f000000) == 0x37000000)
                                                return OP_tbnz;
                                            if ((enc & 0x7f000000) == 0x36000000)
                                                return OP_tbz;
                                        } else {
                                            if ((enc >> 15 & 1) == 0) {
                                                if ((enc & 0xbfe0fc00) == 0x2ee01c00)
                                                    return OP_bif;
                                                if ((enc & 0xbfe0fc00) == 0x2e601c00)
                                                    return OP_bsl;
                                                if ((enc & 0xbfe0fc00) == 0x2e401c00)
                                                    return OP_fmul;
                                            } else {
                                                if ((enc & 0xbf20fc00) == 0x2e209c00)
                                                    return OP_pmul;
                                            }
                                        }
                                    }
                                } else {
                                    if ((enc >> 27 & 1) == 0) {
                                        if ((enc & 0x7f000000) == 0x37000000)
                                            return OP_tbnz;
                                        if ((enc & 0x7f000000) == 0x36000000)
                                            return OP_tbz;
                                    } else {
                                        if ((enc & 0xbfa0fc00) == 0x2e20dc00)
                                            return OP_fmul;
                                        if ((enc & 0xbf20fc00) == 0x2e205c00)
                                            return OP_uqrshl;
                                    }
                                }
                            } else {
                                if ((enc >> 14 & 1) == 0) {
                                    if ((enc >> 27 & 1) == 0) {
                                        if ((enc & 0x7f000000) == 0x37000000)
                                            return OP_tbnz;
                                        if ((enc & 0x7f000000) == 0x36000000)
                                            return OP_tbz;
                                    } else {
                                        if ((enc & 0xbf20fc00) == 0x2e203c00)
                                            return OP_cmhs;
                                        if ((enc & 0xbfe0fc00) == 0x2e403c00)
                                            return OP_fdiv;
                                    }
                                } else {
                                    if ((enc >> 27 & 1) == 0) {
                                        if ((enc & 0x7f000000) == 0x37000000)
                                            return OP_tbnz;
                                        if ((enc & 0x7f000000) == 0x36000000)
                                            return OP_tbz;
                                    } else {
                                        if ((enc & 0xbfa0fc00) == 0x2e20fc00)
                                            return OP_fdiv;
                                        if ((enc & 0xbf20fc00) == 0x2e207c00)
                                            return OP_uaba;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return false;
}
