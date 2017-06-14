
/* !"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\]^_`abcdefghijklmnopqrstuvwxyz{|}~ */
uint8_t chars[] = 
{
    0xff, /* no map */
    0x00, 0x00, /* space */
    0x5F, /* ! */
    0x7, 0x0, 0x7, /* " */
    0x14, 0x74, 0x1F, 0x74, 0x1F, 0x14, /* # */
    0x24, 0x2A, 0x7F, 0x2A, 0x12, /* $ */
    0x27, 0x15, 0x0F, 0x74, 0x52, 0x71, /* % */
    0x38, 0x4F, 0x4D, 0x53, 0x78, 0x40, /* & */
    0x07, /* ' */
    0x3E, 0x41, /* ( */
    0x41, 0x3E, /* ) */
    0x14, 0x08, 0x3E, 0x08, 0x14, /* * */
    0x08, 0x08, 0x3E, 0x08, 0x08, /* + */
    0x80, 0x60, /* , */
    0x08, 0x08, 0x08, 0x08, 0x08, /* - */
    0x40, /* . */
    0x40, 0x30, 0x0C, 0x03, /* / */
    0x3E, 0x51, 0x49, 0x45, 0x3E, /* 0 */
    0x42, 0x41, 0x7F, 0x40, 0x40, /* 1 */
    0x42, 0x61, 0x51, 0x49, 0x46, /* 2 */
    0x41, 0x49, 0x49, 0x36, /* 3 */
    0x18, 0x14, 0x12, 0x11, 0x7F, 0x10, /* 4 */
    0x4F, 0x49, 0x49, 0x31, /* 5 */
    0x3E, 0x4B, 0x49, 0x49, 0x30, /* 6 */
    0x01, 0x41, 0x31, 0x0D, 0x03, /* 7 */
    0x36, 0x4D, 0x49, 0x59, 0x36, /* 8 */
    0x46, 0x49, 0x49, 0x29, 0x1E, /* 9 */
    0x24, /* : */
    0x80, 0x64, /* ; */
    0x08, 0x14, 0x22,  /* < */
    0x14, 0x14, 0x14, 0x14, 0x14, /* = */
    0x22, 0x14, 0x08, /* > */
    0x59, 0x09, 0x06, /* ? */
    0x38, 0x44, 0x42, 0x5A, 0x52, 0x1C, /* @ */
    0x7E, 0x11, 0x11, 0x11, 0x7E, /* A */
    0x7F, 0x49, 0x49, 0x49, 0x36, /* B */
    0x3E, 0x41, 0x41, 0x41, /* C */
    0x7F, 0x41, 0x41, 0x41, 0x3E, /* D */
    0x7F, 0x49, 0x49, 0x49, /* E */
    0x7F, 0x09, 0x09, 0x09, /* F */
    0x3E, 0x41, 0x49, 0x49, 0x7A, /* G */
    0x7F, 0x08, 0x08, 0x7F, /* H */
    0x41, 0x41, 0x7F, 0x41, 0x41, /* I */
    0x41, 0x41, 0x41, 0x3F, /* J */
    0x7F, 0x08, 0x14, 0x22, 0x41, /* K */
    0x7F, 0x40, 0x40, 0x40, /* L */
    0x7F, 0x02, 0x04, 0x08, 0x04, 0x02, 0x7F, /* M */
    0x7F, 0x02, 0x04, 0x08, 0x7F, /* N */
    0x3E, 0x41, 0x41, 0x41, 0x41, 0x3E, /* O */
    0x7F, 0x09, 0x09, 0x09, 0x06, /* P */
    0x3E, 0x41, 0x41, 0x51, 0x21, 0x5E, /* Q */
    0x7F, 0x09, 0x19, 0x26, 0x40, /* R */
    0x46, 0x49, 0x49, 0x49, 0x31, /* S */
    0x01, 0x01, 0x7F, 0x01, 0x01, /* T */
    0x3F, 0x40, 0x40, 0x40, 0x3F, /* U */
    0x03, 0x0C, 0x30, 0x40, 0x30, 0x0C, 0x03, /* V */
    0x07, 0x38, 0x40, 0x20, 0x18, 0x20, 0x40, 0x38, 0x07, /* W */
    0x41, 0x22, 0x14, 0x08, 0x14, 0x22, 0x41, /* X */
    0x01, 0x02, 0x04, 0x78, 0x04, 0x02, 0x01, /* Y */
    0x61, 0x51, 0x49, 0x45, 0x43, /* Z */
    0x7F, 0x41, 0x41, /* [ */
    0x03, 0x0C, 0x30, 0x40, /* \ */
    0x41, 0x41, 0x7F, /* ] */
    0x04, 0x02, 0x01, 0x02, 0x04, /* ^ */
    0x40, 0x40, 0x40, 0x40, 0x40, /* _ */
    0x01, 0x02, /* ` */
    0x20, 0x54, 0x54, 0x54, 0x78, /* a */
    0x7F, 0x44, 0x44, 0x44, 0x38, /* b */
    0x38, 0x44, 0x44, 0x44, /* c */
    0x38, 0x44, 0x44, 0x44, 0x7F, /* d */
    0x38, 0x54, 0x54, 0x54, 0x58, /* e */
    0x04, 0x04, 0x7E, 0x05, 0x05, 0x01, /* f */
    0x18, 0xA4, 0xA4, 0xA4, 0xFC, /* g */
    0x7F, 0x04, 0x04, 0x78, /* h */
    0x44, 0x7D, 0x40, /* i */
    0x80, 0x84, 0x84, 0x7D, /* j */
    0x7F, 0x10, 0x28, 0x44, /* k */
    0x01, 0x3F, 0x40, 0x40, /* l */
    0x7C, 0x04, 0x04, 0x78, 0x04, 0x04, 0x78, /* m */
    0x7C, 0x04, 0x04, 0x78, /* n */
    0x38, 0x44, 0x44, 0x44, 0x38, /* o */
    0xFC, 0x24, 0x24, 0x24, 0x18, /* p */
    0x18, 0x24, 0x24, 0x24, 0xFC, /* q */
    0x7C, 0x08, 0x04, 0x04, 0x0C, /* r */
    0x58, 0x54, 0x54, 0x24, /* s */
    0x04, 0x04, 0x3F, 0x44, 0x44, 0x40, /* t */
    0x3C, 0x40, 0x40, 0x40, 0x3C, /* u */
    0x0C, 0x30, 0x40, 0x30, 0x0C, /* v */
    0x0C, 0x30, 0x40, 0x20, 0x18, 0x20, 0x40, 0x30, 0x0C, /* w */
    0x44, 0x28, 0x10, 0x28, 0x44, /* x */
    0x04, 0x08, 0x70, 0x08, 0x04, /* y */
    0x44, 0x64, 0x54, 0x4C, 0x44, /* z */
    0x08, 0x08, 0x77, 0x41, /* { */
    0x7F, /* | */
    0x41, 0x77, 0x08, 0x08, /* } */
    0x0C, 0x04, 0x0C, 0x08, 0x0C, /* ~ */
    0x07, 0x05, 0x07, /* degree */
};

typedef enum chars_width_tag
{
    char_width_no_map = 1,
    char_width_space = 2,
    char_width_exclamation = 1,
    char_width_quote = 3,
    char_width_hashtag = 6,
    char_width_dollar = 5,
    char_width_percent = 6,
    char_width_ampersand = 6,
    char_width_apostrophe = 1,
    char_width_left_parenthesis = 2,
    char_width_right_parenthesis = 2,
    char_width_asterisk = 5,
    char_width_plus = 5,
    char_width_comma = 2,
    char_width_minus = 5,
    char_width_dot = 1,
    char_width_slash = 4,
    char_width_0 = 5,
    char_width_1 = 5,
    char_width_2 = 5,
    char_width_3 = 4,
    char_width_4 = 6,
    char_width_5 = 4,
    char_width_6 = 5,
    char_width_7 = 5,
    char_width_8 = 5,
    char_width_9 = 5,
    char_width_colon = 1,
    char_width_semicolon = 2,
    char_width_lt = 3,
    char_width_equal = 5,
    char_width_gt = 3,
    char_width_question = 3,
    char_width_at = 6,
    char_width_A = 5,
    char_width_B = 5,
    char_width_C = 4,
    char_width_D = 5,
    char_width_E = 4,
    char_width_F = 4,
    char_width_G = 5,
    char_width_H = 4,
    char_width_I = 5,
    char_width_J = 4,
    char_width_K = 5,
    char_width_L = 4,
    char_width_M = 7,
    char_width_N = 5,
    char_width_O = 6,
    char_width_P = 5,
    char_width_Q = 6,
    char_width_R = 5,
    char_width_S = 5,
    char_width_T = 5,
    char_width_U = 5,
    char_width_V = 7,
    char_width_W = 9,
    char_width_X = 7,
    char_width_Y = 7,
    char_width_Z = 5,
    char_width_left_square_bracket = 3,
    char_width_backslash = 4,
    char_width_right_square_bracket = 3,
    char_width_circumflex_accent = 5,
    char_width_underscore = 5,
    char_width_grave_accent = 2,
    char_width_a = 5,
    char_width_b = 5,
    char_width_c = 4,
    char_width_d = 5,
    char_width_e = 5,
    char_width_f = 6,
    char_width_g = 5,
    char_width_h = 4,
    char_width_i = 3,
    char_width_j = 4,
    char_width_k = 4,
    char_width_l = 4,
    char_width_m = 7,
    char_width_n = 4,
    char_width_o = 5,
    char_width_p = 5,
    char_width_q = 5,
    char_width_r = 5,
    char_width_s = 4,
    char_width_t = 6,
    char_width_u = 5,
    char_width_v = 5,
    char_width_w = 9,
    char_width_x = 5,
    char_width_y = 5,
    char_width_z = 5,
    char_width_left_curly_bracket = 4,
    char_width_pipe = 1,
    char_width_right_curly_bracket = 4,
    char_width_tilde = 5,
    char_width_degree = 3,
} chars_width_t;

typedef enum chars_offset_tag
{
    char_offset_no_map = 0,
    char_offset_space = char_offset_no_map + char_width_no_map,
    char_offset_exclamation = char_offset_space + char_width_space,
    char_offset_quote = char_offset_exclamation + char_width_exclamation,
    char_offset_hashtag = char_offset_quote + char_width_quote,
    char_offset_dollar = char_offset_hashtag + char_width_hashtag,
    char_offset_percent = char_offset_dollar + char_width_dollar,
    char_offset_ampersand = char_offset_percent + char_width_percent,
    char_offset_apostrophe = char_offset_ampersand + char_width_ampersand,
    char_offset_left_parenthesis = char_offset_apostrophe + char_width_apostrophe,
    char_offset_right_parenthesis = char_offset_left_parenthesis + char_width_left_parenthesis,
    char_offset_asterisk = char_offset_right_parenthesis + char_width_right_parenthesis,
    char_offset_plus = char_offset_asterisk + char_width_asterisk,
    char_offset_comma = char_offset_plus + char_width_plus,
    char_offset_minus = char_offset_comma + char_width_comma,
    char_offset_dot = char_offset_minus + char_width_minus,
    char_offset_slash = char_offset_dot + char_width_dot,
    char_offset_0 = char_offset_slash + char_width_slash,
    char_offset_1 = char_offset_0 + char_width_0,
    char_offset_2 = char_offset_1 + char_width_1,
    char_offset_3 = char_offset_2 + char_width_2,
    char_offset_4 = char_offset_3 + char_width_3,
    char_offset_5 = char_offset_4 + char_width_4,
    char_offset_6 = char_offset_5 + char_width_5,
    char_offset_7 = char_offset_6 + char_width_6,
    char_offset_8 = char_offset_7 + char_width_7,
    char_offset_9 = char_offset_8 + char_width_8,
    char_offset_colon = char_offset_9 + char_width_9,
    char_offset_semicolon = char_offset_colon + char_width_colon,
    char_offset_lt = char_offset_semicolon + char_width_semicolon,
    char_offset_equal = char_offset_lt + char_width_lt,
    char_offset_gt = char_offset_equal + char_width_equal,
    char_offset_question = char_offset_gt + char_width_gt,
    char_offset_at = char_offset_question + char_width_question,
    char_offset_A = char_offset_at + char_width_at,
    char_offset_B = char_offset_A + char_width_A,
    char_offset_C = char_offset_B + char_width_B,
    char_offset_D = char_offset_C + char_width_C,
    char_offset_E = char_offset_D + char_width_D,
    char_offset_F = char_offset_E + char_width_E,
    char_offset_G = char_offset_F + char_width_F,
    char_offset_H = char_offset_G + char_width_G,
    char_offset_I = char_offset_H + char_width_H,
    char_offset_J = char_offset_I + char_width_I,
    char_offset_K = char_offset_J + char_width_J,
    char_offset_L = char_offset_K + char_width_K,
    char_offset_M = char_offset_L + char_width_L,
    char_offset_N = char_offset_M + char_width_M,
    char_offset_O = char_offset_N + char_width_N,
    char_offset_P = char_offset_O + char_width_O,
    char_offset_Q = char_offset_P + char_width_P,
    char_offset_R = char_offset_Q + char_width_Q,
    char_offset_S = char_offset_R + char_width_R,
    char_offset_T = char_offset_S + char_width_S,
    char_offset_U = char_offset_T + char_width_T,
    char_offset_V = char_offset_U + char_width_U,
    char_offset_W = char_offset_V + char_width_V,
    char_offset_X = char_offset_W + char_width_W,
    char_offset_Y = char_offset_X + char_width_X,
    char_offset_Z = char_offset_Y + char_width_Y,
    char_offset_left_square_bracket = char_offset_Z + char_width_Z,
    char_offset_backslash = char_offset_left_square_bracket + char_width_left_square_bracket,
    char_offset_right_square_bracket = char_offset_backslash + char_width_backslash,
    char_offset_circumflex_accent = char_offset_right_square_bracket + char_width_right_square_bracket,
    char_offset_underscore = char_offset_circumflex_accent + char_width_circumflex_accent,
    char_offset_grave_accent = char_offset_underscore + char_width_underscore,
    char_offset_a = char_offset_grave_accent + char_width_grave_accent,
    char_offset_b = char_offset_a + char_width_a,
    char_offset_c = char_offset_b + char_width_b,
    char_offset_d = char_offset_c + char_width_c,
    char_offset_e = char_offset_d + char_width_d,
    char_offset_f = char_offset_e + char_width_e,
    char_offset_g = char_offset_f + char_width_f,
    char_offset_h = char_offset_g + char_width_g,
    char_offset_i = char_offset_h + char_width_h,
    char_offset_j = char_offset_i + char_width_i,
    char_offset_k = char_offset_j + char_width_j,
    char_offset_l = char_offset_k + char_width_k,
    char_offset_m = char_offset_l + char_width_l,
    char_offset_n = char_offset_m + char_width_m,
    char_offset_o = char_offset_n + char_width_n,
    char_offset_p = char_offset_o + char_width_o,
    char_offset_q = char_offset_p + char_width_p,
    char_offset_r = char_offset_q + char_width_q,
    char_offset_s = char_offset_r + char_width_r,
    char_offset_t = char_offset_s + char_width_s,
    char_offset_u = char_offset_t + char_width_t,
    char_offset_v = char_offset_u + char_width_u,
    char_offset_w = char_offset_v + char_width_v,
    char_offset_x = char_offset_w + char_width_w,
    char_offset_y = char_offset_x + char_width_x,
    char_offset_z = char_offset_y + char_width_y,
    char_offset_left_curly_bracket = char_offset_z + char_width_z,
    char_offset_pipe = char_offset_left_curly_bracket + char_width_left_curly_bracket,
    char_offset_right_curly_bracket = char_offset_pipe + char_width_pipe,
    char_offset_tilde = char_offset_right_curly_bracket + char_width_right_curly_bracket,
    char_offset_degree = char_offset_tilde + char_width_tilde,
} chars_offset_t;

uint16_t chars_map[][2] =
{
    {char_width_space, char_offset_space},
    {char_width_exclamation, char_offset_exclamation},
    {char_width_quote, char_offset_quote},
    {char_width_hashtag, char_offset_hashtag},
    {char_width_dollar, char_offset_dollar},
    {char_width_percent, char_offset_percent},
    {char_width_ampersand, char_offset_ampersand},
    {char_width_apostrophe, char_offset_apostrophe},
    {char_width_left_parenthesis, char_offset_left_parenthesis},
    {char_width_right_parenthesis, char_offset_right_parenthesis},
    {char_width_asterisk, char_offset_asterisk},
    {char_width_plus, char_offset_plus},
    {char_width_comma, char_offset_comma},
    {char_width_minus, char_offset_minus},
    {char_width_dot, char_offset_dot},
    {char_width_slash, char_offset_slash},
    {char_width_0, char_offset_0},
    {char_width_1, char_offset_1},
    {char_width_2, char_offset_2},
    {char_width_3, char_offset_3},
    {char_width_4, char_offset_4},
    {char_width_5, char_offset_5},
    {char_width_6, char_offset_6},
    {char_width_7, char_offset_7},
    {char_width_8, char_offset_8},
    {char_width_9, char_offset_9},
    {char_width_colon, char_offset_colon},
    {char_width_semicolon, char_offset_semicolon},
    {char_width_lt, char_offset_lt},
    {char_width_equal, char_offset_equal},
    {char_width_gt, char_offset_gt},
    {char_width_question, char_offset_question},
    {char_width_at, char_offset_at},
    {char_width_A, char_offset_A},
    {char_width_B, char_offset_B},
    {char_width_C, char_offset_C},
    {char_width_D, char_offset_D},
    {char_width_E, char_offset_E},
    {char_width_F, char_offset_F},
    {char_width_G, char_offset_G},
    {char_width_H, char_offset_H},
    {char_width_I, char_offset_I},
    {char_width_J, char_offset_J},
    {char_width_K, char_offset_K},
    {char_width_L, char_offset_L},
    {char_width_M, char_offset_M},
    {char_width_N, char_offset_N},
    {char_width_O, char_offset_O},
    {char_width_P, char_offset_P},
    {char_width_Q, char_offset_Q},
    {char_width_R, char_offset_R},
    {char_width_S, char_offset_S},
    {char_width_T, char_offset_T},
    {char_width_U, char_offset_U},
    {char_width_V, char_offset_V},
    {char_width_W, char_offset_W},
    {char_width_X, char_offset_X},
    {char_width_Y, char_offset_Y},
    {char_width_Z, char_offset_Z},
    {char_width_left_square_bracket, char_offset_left_square_bracket},
    {char_width_backslash, char_offset_backslash},
    {char_width_right_square_bracket, char_offset_right_square_bracket},
    {char_width_circumflex_accent, char_offset_circumflex_accent},
    {char_width_underscore, char_offset_underscore},
    {char_width_grave_accent, char_offset_grave_accent},
    {char_width_a, char_offset_a},
    {char_width_b, char_offset_b},
    {char_width_c, char_offset_c},
    {char_width_d, char_offset_d},
    {char_width_e, char_offset_e},
    {char_width_f, char_offset_f},
    {char_width_g, char_offset_g},
    {char_width_h, char_offset_h},
    {char_width_i, char_offset_i},
    {char_width_j, char_offset_j},
    {char_width_k, char_offset_k},
    {char_width_l, char_offset_l},
    {char_width_m, char_offset_m},
    {char_width_n, char_offset_n},
    {char_width_o, char_offset_o},
    {char_width_p, char_offset_p},
    {char_width_q, char_offset_q},
    {char_width_r, char_offset_r},
    {char_width_s, char_offset_s},
    {char_width_t, char_offset_t},
    {char_width_u, char_offset_u},
    {char_width_v, char_offset_v},
    {char_width_w, char_offset_w},
    {char_width_x, char_offset_x},
    {char_width_y, char_offset_y},
    {char_width_z, char_offset_z},
    {char_width_left_curly_bracket, char_offset_left_curly_bracket},
    {char_width_pipe, char_offset_pipe},
    {char_width_right_curly_bracket, char_offset_right_curly_bracket},
    {char_width_tilde, char_offset_tilde},
    {char_width_no_map, char_offset_no_map},
    {char_width_no_map, char_offset_no_map},
    {char_width_no_map, char_offset_no_map},
    {char_width_no_map, char_offset_no_map},
    {char_width_no_map, char_offset_no_map},
    {char_width_no_map, char_offset_no_map},
    {char_width_no_map, char_offset_no_map},
    {char_width_no_map, char_offset_no_map},
    {char_width_no_map, char_offset_no_map},
    {char_width_no_map, char_offset_no_map},
    {char_width_no_map, char_offset_no_map},
    {char_width_no_map, char_offset_no_map},
    {char_width_no_map, char_offset_no_map},
    {char_width_no_map, char_offset_no_map},
    {char_width_no_map, char_offset_no_map},
    {char_width_no_map, char_offset_no_map},
    {char_width_no_map, char_offset_no_map},
    {char_width_no_map, char_offset_no_map},
    {char_width_no_map, char_offset_no_map},
    {char_width_no_map, char_offset_no_map},
    {char_width_no_map, char_offset_no_map},
    {char_width_no_map, char_offset_no_map},
    {char_width_no_map, char_offset_no_map},
    {char_width_no_map, char_offset_no_map},
    {char_width_no_map, char_offset_no_map},
    {char_width_no_map, char_offset_no_map},
    {char_width_no_map, char_offset_no_map},
    {char_width_no_map, char_offset_no_map},
    {char_width_no_map, char_offset_no_map},
    {char_width_no_map, char_offset_no_map},
    {char_width_no_map, char_offset_no_map},
    {char_width_no_map, char_offset_no_map},
    {char_width_no_map, char_offset_no_map},
    {char_width_no_map, char_offset_no_map},
    {char_width_no_map, char_offset_no_map},
    {char_width_no_map, char_offset_no_map},
    {char_width_no_map, char_offset_no_map},
    {char_width_no_map, char_offset_no_map},
    {char_width_no_map, char_offset_no_map},
    {char_width_no_map, char_offset_no_map},
    {char_width_no_map, char_offset_no_map},
    {char_width_no_map, char_offset_no_map},
    {char_width_no_map, char_offset_no_map},
    {char_width_no_map, char_offset_no_map},
    {char_width_no_map, char_offset_no_map},
    {char_width_no_map, char_offset_no_map},
    {char_width_no_map, char_offset_no_map},
    {char_width_no_map, char_offset_no_map},
    {char_width_no_map, char_offset_no_map},
    {char_width_no_map, char_offset_no_map},
    {char_width_no_map, char_offset_no_map},
    {char_width_no_map, char_offset_no_map},
    {char_width_no_map, char_offset_no_map},
    {char_width_no_map, char_offset_no_map},
    {char_width_no_map, char_offset_no_map},
    {char_width_no_map, char_offset_no_map},
    {char_width_no_map, char_offset_no_map},
    {char_width_no_map, char_offset_no_map},
    {char_width_no_map, char_offset_no_map},
    {char_width_no_map, char_offset_no_map},
    {char_width_no_map, char_offset_no_map},
    {char_width_no_map, char_offset_no_map},
    {char_width_no_map, char_offset_no_map},
    {char_width_no_map, char_offset_no_map},
    {char_width_no_map, char_offset_no_map},
    {char_width_no_map, char_offset_no_map},
    {char_width_no_map, char_offset_no_map},
    {char_width_no_map, char_offset_no_map},
    {char_width_no_map, char_offset_no_map},
    {char_width_no_map, char_offset_no_map},
    {char_width_no_map, char_offset_no_map},
    {char_width_no_map, char_offset_no_map},
    {char_width_no_map, char_offset_no_map},
    {char_width_no_map, char_offset_no_map},
    {char_width_no_map, char_offset_no_map},
    {char_width_no_map, char_offset_no_map},
    {char_width_no_map, char_offset_no_map},
    {char_width_no_map, char_offset_no_map},
    {char_width_no_map, char_offset_no_map},
    {char_width_no_map, char_offset_no_map},
    {char_width_no_map, char_offset_no_map},
    {char_width_no_map, char_offset_no_map},
    {char_width_no_map, char_offset_no_map},
    {char_width_no_map, char_offset_no_map},
    {char_width_no_map, char_offset_no_map},
    {char_width_no_map, char_offset_no_map},
    {char_width_no_map, char_offset_no_map},
    {char_width_no_map, char_offset_no_map},
    {char_width_no_map, char_offset_no_map},
    {char_width_no_map, char_offset_no_map},
    {char_width_no_map, char_offset_no_map},
    {char_width_no_map, char_offset_no_map},
    {char_width_no_map, char_offset_no_map},
    {char_width_no_map, char_offset_no_map},
    {char_width_no_map, char_offset_no_map},
    {char_width_no_map, char_offset_no_map},
    {char_width_no_map, char_offset_no_map},
    {char_width_no_map, char_offset_no_map},
    {char_width_no_map, char_offset_no_map},
    {char_width_no_map, char_offset_no_map},
    {char_width_no_map, char_offset_no_map},
    {char_width_no_map, char_offset_no_map},
    {char_width_no_map, char_offset_no_map},
    {char_width_no_map, char_offset_no_map},
    {char_width_no_map, char_offset_no_map},
    {char_width_no_map, char_offset_no_map},
    {char_width_no_map, char_offset_no_map},
    {char_width_no_map, char_offset_no_map},
    {char_width_no_map, char_offset_no_map},
    {char_width_no_map, char_offset_no_map},
    {char_width_no_map, char_offset_no_map},
    {char_width_no_map, char_offset_no_map},
    {char_width_no_map, char_offset_no_map},
    {char_width_no_map, char_offset_no_map},
    {char_width_no_map, char_offset_no_map},
    {char_width_no_map, char_offset_no_map},
    {char_width_no_map, char_offset_no_map},
    {char_width_no_map, char_offset_no_map},
    {char_width_no_map, char_offset_no_map},
    {char_width_no_map, char_offset_no_map},
    {char_width_no_map, char_offset_no_map},
    {char_width_degree, char_offset_degree},
};
