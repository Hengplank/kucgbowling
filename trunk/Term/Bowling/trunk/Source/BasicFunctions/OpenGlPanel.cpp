#include "stdafx.h"
#include "BasicFunctions.h"
#include "OpenGlPanel.h"
#include "PixelFormatController.h"
#include "PixelFormat.h"
#include "Lighting.h"
#include <glut.h>

using namespace OpenGl;

IMPLEMENT_DYNAMIC(OpenGlPanel, CWnd)

OpenGlPanel::OpenGlPanel()
    : clientDc_(nullptr)
    , rotation_(0.0)
    , renderingContext_(nullptr)
    , isLButtonDown_(false)
    , isRButtonDown_(false)
    , isMButtonDown_(false)
{
}

OpenGlPanel::~OpenGlPanel()
{
    if(renderingContext_ != nullptr)
    {
        delete renderingContext_;
    }

    if(clientDc_ != nullptr)
    {
        delete clientDc_;
    }
}

BEGIN_MESSAGE_MAP(OpenGlPanel, CWnd)
    ON_WM_SIZE()
    ON_WM_PAINT()
    ON_WM_ERASEBKGND()
    ON_WM_CREATE()
//    ON_WM_MOUSEHWHEEL()
    ON_WM_MOUSELEAVE()
    ON_WM_MOUSEMOVE()
    ON_WM_MOUSEWHEEL()
    ON_WM_RBUTTONDOWN()
    ON_WM_RBUTTONUP()
    ON_WM_LBUTTONDOWN()
    ON_WM_LBUTTONUP()
    ON_WM_MBUTTONDOWN()
    ON_WM_MBUTTONUP()
    ON_WM_MOUSEHWHEEL()
END_MESSAGE_MAP()

void OpenGlPanel::Create(CRect rect, CWnd* parent)
{
    CString className = AfxRegisterWndClass(CS_HREDRAW | CS_VREDRAW | CS_OWNDC, NULL, reinterpret_cast<HBRUSH>(GetStockObject(BLACK_BRUSH)), NULL);

    CreateEx(0, className, L"OpenGlPanel", WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN, rect, parent, 0);
}

void OpenGlPanel::OnSize(UINT nType, int cx, int cy)
{
    CWnd::OnSize(nType, cx, cy);

    if(cy == 0)
    {
        cy = 1;
    }
    //glViewport(0, 0, cx, cy);
    width_ = cx;
    height_ = cy;

    double aspect = static_cast<double>(cx / cy);
    camera_.SetAspect(aspect);
    camera_.Apply();

   /* topCamera_.SetAspect(aspect);
    topCamera_.Apply();
    frontCamera_.SetAspect(aspect);
    frontCamera_.Apply();
    sideCamera_.SetAspect(aspect);
    sideCamera_.Apply();*/
}

void OpenGlPanel::InitializeOpenGl()
{
    glEnable(GL_TEXTURE_2D);
    glShadeModel(GL_SMOOTH);
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClearDepth(1.0);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}

void OpenGlPanel::DrawScene()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Top Left(TOP VIEW)
    //glViewport(0, height_/2, width_/2, height_/2);
    //topCamera_.Apply();
    //anotherSprite_.Draw();
    //
    //// Top Right(FRONT VIEW)
    //glViewport(width_/2, height_/2, width_/2, height_/2);
    //frontCamera_.Apply();
    //anotherSprite_.Draw();

    //// Bottom Left(SIDE VIEW)
    //glViewport(0, 0, width_/2, height_/2);
    //sideCamera_.Apply();
    //anotherSprite_.Draw();

    //// Bottom Right(USER VIEW)
    //glViewport(width_/2, 0, width_/2, height_/2);
    //camera_.Apply();
    //sprite_.Draw();
	glViewport(0, 0, width_, height_);
	camera_.Apply();
	sprite_.Draw();
	spritePin_.Draw();
	spritePin2_.Draw();
	spritePin3_.Draw();
	spritePin4_.Draw();
	spritePin5_.Draw();
	spritePin6_.Draw();
	spritePin7_.Draw();
	spritePin8_.Draw();
	spritePin9_.Draw();
	spritePin10_.Draw();
    SwapBuffers(clientDc_->m_hDC);
}

void OpenGlPanel::OnPaint()
{
    CPaintDC dc(this); // device context for painting
    // TODO: 여기에 메시지 처리기 코드를 추가합니다.
    // 그리기 메시지에 대해서는 CWnd::OnPaint()을(를) 호출하지 마십시오.

    renderingContext_->SetThisCurrent(clientDc_->m_hDC);
    rotation_ += 0.1;
    if(rotation_ >= 360.0)
    {
        rotation_ -= 360.0;
    }
    DrawScene();
}


BOOL OpenGlPanel::OnEraseBkgnd(CDC* pDC)
{
    return TRUE;
    //return CWnd::OnEraseBkgnd(pDC);
}


int OpenGlPanel::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    if (CWnd::OnCreate(lpCreateStruct) == -1)
        return -1;

    clientDc_ = new CClientDC(this);
    SetupPixelFormat(clientDc_->m_hDC);

    renderingContext_ = new RenderingContext(clientDc_->m_hDC);
    renderingContext_->SetThisCurrent(clientDc_->m_hDC);

    InitializeOpenGl();

    return 0;
}

void OpenGlPanel::SetupPixelFormat(HDC hDC)
{
    int bits = 32;
    
    PixelFormatController controller;
    controller.SetPixelFormat(hDC, PixelFormat(
        1,
        PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER, 
        PFD_TYPE_RGBA,
        bits,
        0, 0, 0, 0, 0, 0,
        0,
        0,
        0,
        0, 0, 0, 0,
        16,
        0,
        0,
        PFD_MAIN_PLANE,
        0, 0, 0));
}

Virgin::Sprite& OpenGlPanel::Sprite()
{
    return sprite_;
}

Virgin::Sprite& OpenGlPanel::SpritePin()
{
    return spritePin_;
}

Virgin::Sprite& OpenGlPanel::SpritePin2()
{
    return spritePin2_;
}

Virgin::Sprite& OpenGlPanel::SpritePin3()
{
    return spritePin3_;
}

Virgin::Sprite& OpenGlPanel::SpritePin4()
{
    return spritePin4_;
}

Virgin::Sprite& OpenGlPanel::SpritePin5()
{
    return spritePin5_;
}

Virgin::Sprite& OpenGlPanel::SpritePin6()
{
    return spritePin6_;
}

Virgin::Sprite& OpenGlPanel::SpritePin7()
{
    return spritePin7_;
}

Virgin::Sprite& OpenGlPanel::SpritePin8()
{
    return spritePin8_;
}

Virgin::Sprite& OpenGlPanel::SpritePin9()
{
    return spritePin9_;
}

Virgin::Sprite& OpenGlPanel::SpritePin10()
{
    return spritePin10_;
}

Virgin::Camera& OpenGlPanel::Camera()
{
    return camera_;
}


void OpenGlPanel::OnMouseLeave()
{
    // TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

    CWnd::OnMouseLeave();
}


void OpenGlPanel::OnMouseMove(UINT nFlags, CPoint point)
{
    static CPoint lastPoint = point;

    if(isLButtonDown_)
    {
        CPoint pointDelta = point - lastPoint;
        float moveX = (float)pointDelta.x / 100.0;
        float moveY = (float)pointDelta.y / 100.0;
        GetManipulatingSprite().TranslateMore(moveX, -moveY, 0.0);
    }
    else if(isRButtonDown_)
    {
        CPoint pointDelta = point - lastPoint;
        float moveX = (float)pointDelta.x / 5.0;
        float moveY = (float)pointDelta.y / 5.0;
        GetManipulatingSprite().RotateXMore(moveY);
        GetManipulatingSprite().RotateYMore(moveX);
    }
    else if(isMButtonDown_)
    {
        // Y가 커지면 가까이
        CPoint pointDelta = point - lastPoint;
        /*float rate = 1.0 + ((float)pointDelta.y / 100.0);
        sprite_.ScaleRate(rate, rate, rate);*/
        float move = (float)pointDelta.y / 100.0;
        GetManipulatingSprite().TranslateMore(0.0, 0.0, move);
    }

    lastPoint = point;

    CWnd::OnMouseMove(nFlags, point);
}


BOOL OpenGlPanel::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
    if(zDelta < 0)
    {
        // 확대
        //sprite_.ScaleRate(1.5, 1.5, 1.5);
    }
    else
    {
        // 축소
    }

    return CWnd::OnMouseWheel(nFlags, zDelta, pt);
}


void OpenGlPanel::OnRButtonDown(UINT nFlags, CPoint point)
{
    isRButtonDown_ = true;

    CWnd::OnRButtonDown(nFlags, point);
}


void OpenGlPanel::OnRButtonUp(UINT nFlags, CPoint point)
{
    isRButtonDown_ = false;

    CWnd::OnRButtonUp(nFlags, point);
}


void OpenGlPanel::OnLButtonDown(UINT nFlags, CPoint point)
{
    isLButtonDown_ = true;

    CWnd::OnLButtonDown(nFlags, point);
}


void OpenGlPanel::OnLButtonUp(UINT nFlags, CPoint point)
{
    isLButtonDown_ = false;

    CWnd::OnLButtonUp(nFlags, point);
}


void OpenGlPanel::OnMButtonDown(UINT nFlags, CPoint point)
{
    isMButtonDown_ = true;

    CWnd::OnMButtonDown(nFlags, point);
}


void OpenGlPanel::OnMButtonUp(UINT nFlags, CPoint point)
{
    isMButtonDown_ = false;

    CWnd::OnMButtonUp(nFlags, point);
}


void OpenGlPanel::OnMouseHWheel(UINT nFlags, short zDelta, CPoint pt)
{
    // 이 기능을 사용하려면 Windows Vista 이상이 있어야 합니다.
    // _WIN32_WINNT 기호는 0x0600보다 크거나 같아야 합니다.
    // TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
    OnMouseWheel(nFlags, zDelta, pt);

    CWnd::OnMouseHWheel(nFlags, zDelta, pt);
}

Virgin::Light& OpenGlPanel::Light()
{
    return light_;
}
