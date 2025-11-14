#include "textHelper.hh"

#include "main.hh"
#include "position.hh"

#include <SDL3_ttf/SDL_ttf.h>

#include <stdexcept>

#define PT_SIZE_TINY 8
#define PT_SIZE_SMALL 12
#define PT_SIZE_MEDIUM 18
#define PT_SIZE_LARGE 26
#define PT_SIZE_EXTRA_LARGE 36

#define DEFAULT_FONT_FILE "./fonts/wiltype/wiltype.ttf"
#define TITLE_FONT_FILE "./fonts/wiltype/wiltype.ttf"

namespace common {

struct font_t {
	TTF_Font* internal;

	// the next size down of this font, or nullptr if no smaller size
	font_t* downsize;
};

font_t fonts[font::INVALID];

inline bool fontFits(int w, int h, const char* str, TTF_Font* font) {
	int mw, mh;
	TTF_GetStringSize(font, str, 0, &mw, &mh);
	return w <= mw && h <= mh;
}

inline TTF_Font* findFont(int w, int h, string& str, font font) {
	if (font == font::INVALID)
		return nullptr;
	const char* cstr = str.c_str();
	font_t* guess = &fonts[font];
	while (!fontFits(w, h, cstr, guess->internal)) {
		guess = guess->downsize;
		if (guess == nullptr)
			return nullptr;
	}
	return guess->internal;
}

void renderText(const position& pos, string& str, font font) {
	TTF_Font* sdlfont = findFont(pos.width, pos.height, str, font);
	if (sdlfont == nullptr)
		throw new std::runtime_error("String too long for display");

	int w, h;
	TTF_Text* text = TTF_CreateText(textEngine, sdlfont, str.c_str(), 0);
	TTF_GetTextSize(text, &w, &h);

	int xbuf = pos.width - w;
	int ybuf = pos.height - h;
	float x, y;
	switch (pos.anchor & ALIGN_HORIZONTAL_MASK) {
	case ALIGN_HORIZONTAL_LEFT:
		x = pos.xOffset;
		break;
	case ALIGN_HORIZONTAL_CENTER:
		x = pos.xOffset + static_cast<float>(xbuf) / 2;
		break;
	case ALIGN_HORIZONTAL_RIGHT:
		x = pos.xOffset + static_cast<float>(xbuf);
		break;
	default:
		throw new std::invalid_argument("invalid anchor mask (horizontal bits)");
	}
	switch (pos.anchor & ALIGN_VERTICAL_MASK) {
	case ALIGN_VERTICAL_TOP:
		y = pos.yOffset;
		break;
	case ALIGN_VERTICAL_CENTER:
		y = pos.yOffset + static_cast<float>(ybuf) / 2;
		break;
	case ALIGN_VERTICAL_BOTTOM:
		y = pos.yOffset + static_cast<float>(ybuf);
		break;
	default:
		throw new std::invalid_argument("invalid anchor mask (vertical bits)");
	}

	TTF_DrawRendererText(text, x, y);
}

inline TTF_Font* requireFont(const char* path, float ptsize) {
	TTF_Font* fnt = TTF_OpenFont(path, ptsize);
	if (fnt == NULL)
		throw new std::runtime_error("Failed to open font");
}

void initTextHelper() {
	fonts[font::TINY].internal = TTF_OpenFont(DEFAULT_FONT_FILE, PT_SIZE_TINY);
	fonts[font::SMALL].internal = TTF_OpenFont(DEFAULT_FONT_FILE, PT_SIZE_SMALL);
	fonts[font::MEDIUM].internal = TTF_OpenFont(DEFAULT_FONT_FILE, PT_SIZE_MEDIUM);
	fonts[font::LARGE].internal = TTF_OpenFont(DEFAULT_FONT_FILE, PT_SIZE_LARGE);
	fonts[font::EXTRA_LARGE].internal = TTF_OpenFont(DEFAULT_FONT_FILE, PT_SIZE_EXTRA_LARGE);
	fonts[font::TITLE_MEDIUM].internal = TTF_OpenFont(TITLE_FONT_FILE, PT_SIZE_MEDIUM);
	fonts[font::TITLE_LARGE].internal = TTF_OpenFont(TITLE_FONT_FILE, PT_SIZE_LARGE);
	fonts[font::TITLE_EXTRA_LARGE].internal = TTF_OpenFont(TITLE_FONT_FILE, PT_SIZE_EXTRA_LARGE);

	fonts[font::SMALL].downsize = &fonts[font::TINY];
	fonts[font::MEDIUM].downsize = &fonts[font::SMALL];
	fonts[font::LARGE].downsize = &fonts[font::MEDIUM];
	fonts[font::EXTRA_LARGE].downsize = &fonts[font::LARGE];
	fonts[font::TITLE_LARGE].downsize = &fonts[font::TITLE_MEDIUM];
	fonts[font::TITLE_EXTRA_LARGE].downsize = &fonts[font::TITLE_LARGE];
}

void quitTextHelper() {
	for (int i = 0; i < font::INVALID; i++)
		TTF_CloseFont(fonts[i].internal);
}

} // namespace common
