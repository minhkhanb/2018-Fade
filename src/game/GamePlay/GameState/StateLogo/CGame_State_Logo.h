#ifndef __COLORBORN_EXAMPLE__
#define __COLORBORN_EXAMPLE__

class StateLogo
{
public:
	PineImage _image_logo;
	static int _loading_step;
	bool _optimizeData;
	bool _autoLoading;
	void InitLogo();
	void RenderLogo();
	void UpdateLogo();
	int _state;
	float _scroll_page_y;
	Acceleration _acceleration_scroll;
    float _percent_volumn;
private:

};
#endif // !__COLORBORN_EXAMPLE__
