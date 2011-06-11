
// BasicFunctionsDlg.cpp : ���� ����
//

#include "stdafx.h"
#include "BasicFunctions.h"
#include "BasicFunctionsDlg.h"
#include "afxdialogex.h"
#include "Lighting.h"
#include <gl/GL.h>
#include <glut.h>

#include <Mmsystem.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


using namespace Virgin;

// ���� ���α׷� ������ ���Ǵ� CAboutDlg ��ȭ �����Դϴ�.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

// �����Դϴ�.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CBasicFunctionsDlg ��ȭ ����




CBasicFunctionsDlg::CBasicFunctionsDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CBasicFunctionsDlg::IDD, pParent)
    , rotateLeftButtonDown_(false)
    , rotateRightButtonDown_(false)
    , rotateUpButtonDown_(false)
    , rotateDownButtonDown_(false)
    , rollLeftButtonDown_(false)
    , rollRightButtonDown_(false)
    , moveUpButtonDown_(false)
    , moveDownButtonDown_(false)
    , moveLeftButtonDown_(false)
    , moveRightButtonDown_(false)
    , moveFarButtonDown_(false)
    , moveNearButtonDown_(false)
    , biggerButtonDown_(false)
    , smallerButtonDown_(false)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CBasicFunctionsDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_DISPLAY_PANEL, displayPanel_);
    DDX_Control(pDX, IDC_ROTATE_LEFT_BUTTON, rotateLeftButton_);
    DDX_Control(pDX, IDC_ROTATE_RIGHT_BUTTON, rotateRightButton_);
    DDX_Control(pDX, IDC_ROTATE_UP_BUTTON, rotateUpButton_);
    DDX_Control(pDX, IDC_ROLL_LEFT_BUTTON, rollLeftButton_);
    DDX_Control(pDX, IDC_ROLL_RIGHT_BUTTON, rollRightButton_);
    DDX_Control(pDX, IDC_ROTATE_DOWN_BUTTON, rotateDownButton_);
    DDX_Control(pDX, IDC_MOVE_FAR_BUTTON, moveFarButton_);
    DDX_Control(pDX, IDC_MOVE_NEAR_BUTTON, moveNearButton_);
    DDX_Control(pDX, IDC_LEFT_BUTTON, moveLeftButton_);
    DDX_Control(pDX, IDC_RIGHT_BUTTON, moveRightButton_);
    DDX_Control(pDX, IDC_UP_BUTTON, moveUpButton_);
    DDX_Control(pDX, IDC_DOWN_BUTTON, moveDownButton_);
    DDX_Control(pDX, IDC_MOVE_FAR_BUTTON2, biggerButton_);
    DDX_Control(pDX, IDC_MOVE_NEAR_BUTTON2, smallerButton_);
    DDX_Control(pDX, IDC_SCALE_X_EDIT, scaleXEdit_);
    DDX_Control(pDX, IDC_SCALE_Y_EDIT, scaleYEdit_);
    DDX_Control(pDX, IDC_SCALE_Z_EDIT, scaleZEdit_);
    DDX_Control(pDX, IDC_DRAW_NORMAL_CHECK, drawNormalCheck_);
    DDX_Control(pDX, IDC_FPS_STATIC, fpsStatic_);
    DDX_Control(pDX, IDC_SPEED_SLIDER, speedSlider_);
    DDX_Control(pDX, IDC_CAMERA_LOCATION_X_EDIT, cameraLocationXEdit_);
    DDX_Control(pDX, IDC_CAMERA_LOCATION_Y_EDIT, cameraLocationYEdit_);
    DDX_Control(pDX, IDC_CAMERA_LOCATION_Z_EDIT, cameraLocationZEdit_);
    DDX_Control(pDX, IDC_CAMERA_LOOKAT_X_EDIT, cameraLookAtXEdit_);
    DDX_Control(pDX, IDC_CAMERA_LOOKAT_Y_EDIT, cameraLookAtYEdit_);
    DDX_Control(pDX, IDC_CAMERA_LOOKAT_Z_EDIT, cameraLookAtZEdit_);
    DDX_Control(pDX, IDC_CAMERA_UP_X_EDIT, cameraUpXEdit_);
    DDX_Control(pDX, IDC_CAMERA_UP_Y_EDIT, cameraUpYEdit_);
    DDX_Control(pDX, IDC_CAMERA_UP_Z_EDIT, cameraUpZEdit_);
    DDX_Control(pDX, IDC_CAMERA_AUTO_ROTATION_CHECK, cameraAutoRotateCheck_);
    DDX_Control(pDX, IDC_AMBIENT_R_EDIT, ambientREdit_);
    DDX_Control(pDX, IDC_AMBIENT_G_EDIT, ambientGEdit_);
    DDX_Control(pDX, IDC_AMBIENT_B_EDIT, ambientBEdit_);
    DDX_Control(pDX, IDC_DIFFUSE_R_EDIT, diffuseREdit_);
    DDX_Control(pDX, IDC_DIFFUSE_G_EDIT, diffuseGEdit_);
    DDX_Control(pDX, IDC_DIFFUSE_B_EDIT, diffuseBEdit_);
    DDX_Control(pDX, IDC_SPECULAR_R_EDIT, specularREdit_);
    DDX_Control(pDX, IDC_SPECULAR_G_EDIT, specularGEdit_);
    DDX_Control(pDX, IDC_SPECULAR_B_EDIT, specularBEdit_);
    DDX_Control(pDX, IDC_LIGHT_CHECK, lightCheck_);
    DDX_Control(pDX, IDC_USER_VIEW_SELECTED_CHECK, userViewSelectedCheck_);
    DDX_Control(pDX, IDC_DRAW_TEXTURE_CHECK, drawTextureCheck_);
}

BEGIN_MESSAGE_MAP(CBasicFunctionsDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
    ON_WM_ERASEBKGND()
    ON_WM_SIZE()
    ON_WM_DESTROY()
    ON_BN_CLICKED(IDC_ROTATE_LEFT_BUTTON, &CBasicFunctionsDlg::OnBnClickedRotateLeftButton)
    ON_BN_CLICKED(IDC_RESET_SPRITE_BUTTON, &CBasicFunctionsDlg::OnBnClickedResetSpriteButton)

    // Arbitrary Axis Rotation
    ON_EN_CHANGE(IDC_ARBITRARY_AXIS_FROM_X_EDIT, &CBasicFunctionsDlg::OnEditChange)
    ON_EN_CHANGE(IDC_ARBITRARY_AXIS_FROM_Y_EDIT, &CBasicFunctionsDlg::OnEditChange)
    ON_EN_CHANGE(IDC_ARBITRARY_AXIS_FROM_Z_EDIT, &CBasicFunctionsDlg::OnEditChange)
    ON_EN_CHANGE(IDC_ARBITRARY_AXIS_TO_X_EDIT, &CBasicFunctionsDlg::OnEditChange)
    ON_EN_CHANGE(IDC_ARBITRARY_AXIS_TO_Y_EDIT, &CBasicFunctionsDlg::OnEditChange)
    ON_EN_CHANGE(IDC_ARBITRARY_AXIS_TO_Z_EDIT, &CBasicFunctionsDlg::OnEditChange)
    ON_EN_CHANGE(IDC_ARBITRARY_ROTATE_ANGLE_EDIT, &CBasicFunctionsDlg::OnEditChange)

    // Camera Position, Looking at, Up
    ON_EN_CHANGE(IDC_CAMERA_LOCATION_X_EDIT, &CBasicFunctionsDlg::OnEditChange)
    ON_EN_CHANGE(IDC_CAMERA_LOCATION_Y_EDIT, &CBasicFunctionsDlg::OnEditChange)
    ON_EN_CHANGE(IDC_CAMERA_LOCATION_Z_EDIT, &CBasicFunctionsDlg::OnEditChange)
    ON_EN_CHANGE(IDC_CAMERA_LOOKAT_X_EDIT, &CBasicFunctionsDlg::OnEditChange)
    ON_EN_CHANGE(IDC_CAMERA_LOOKAT_Y_EDIT, &CBasicFunctionsDlg::OnEditChange)
    ON_EN_CHANGE(IDC_CAMERA_LOOKAT_Z_EDIT, &CBasicFunctionsDlg::OnEditChange)
    ON_EN_CHANGE(IDC_CAMERA_UP_X_EDIT, &CBasicFunctionsDlg::OnEditChange)
    ON_EN_CHANGE(IDC_CAMERA_UP_Y_EDIT, &CBasicFunctionsDlg::OnEditChange)
    ON_EN_CHANGE(IDC_CAMERA_UP_Z_EDIT, &CBasicFunctionsDlg::OnEditChange)
    
    // Scaling
    ON_EN_CHANGE(IDC_SCALE_X_EDIT, &CBasicFunctionsDlg::OnEditChange)
    ON_EN_CHANGE(IDC_SCALE_Y_EDIT, &CBasicFunctionsDlg::OnEditChange)
    ON_EN_CHANGE(IDC_SCALE_Z_EDIT, &CBasicFunctionsDlg::OnEditChange)

    // Pivot-point Scaling
    ON_EN_CHANGE(IDC_PIVOT_POINT_X_EDIT, &CBasicFunctionsDlg::OnEditChange)
    ON_EN_CHANGE(IDC_PIVOT_POINT_Y_EDIT, &CBasicFunctionsDlg::OnEditChange)
    ON_EN_CHANGE(IDC_PIVOT_POINT_Z_EDIT, &CBasicFunctionsDlg::OnEditChange)
    ON_EN_CHANGE(IDC_PIVOT_SCALE_X_EDIT, &CBasicFunctionsDlg::OnEditChange)
    ON_EN_CHANGE(IDC_PIVOT_SCALE_Y_EDIT, &CBasicFunctionsDlg::OnEditChange)
    ON_EN_CHANGE(IDC_PIVOT_SCALE_Z_EDIT, &CBasicFunctionsDlg::OnEditChange)
    ON_BN_CLICKED(IDC_TEST_BUTTON, &CBasicFunctionsDlg::OnBnClickedTestButton)
    ON_BN_CLICKED(IDC_DRAW_NORMAL_CHECK, &CBasicFunctionsDlg::OnBnClickedDrawNormalCheck)
    ON_BN_CLICKED(IDC_MESH_POINT_BUTTON, &CBasicFunctionsDlg::OnBnClickedMeshPointButton)
    ON_BN_CLICKED(IDC_MESH_WIREFRAME_BUTTON, &CBasicFunctionsDlg::OnBnClickedMeshWireframeButton)
    ON_BN_CLICKED(IDC_MESH_QUAD_BUTTON, &CBasicFunctionsDlg::OnBnClickedMeshQuadButton)
    ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SPEED_SLIDER, &CBasicFunctionsDlg::OnNMReleasedcaptureSpeedSlider)
    ON_WM_MOUSEWHEEL()
    ON_BN_CLICKED(IDC_CAMERA_AUTO_ROTATION_CHECK, &CBasicFunctionsDlg::OnBnClickedCameraAutoRotationCheck)
    ON_BN_CLICKED(IDC_LIGHT_CHECK, &CBasicFunctionsDlg::OnBnClickedLightCheck)
    ON_BN_CLICKED(IDC_FLAT_SHADING_BUTTON, &CBasicFunctionsDlg::OnBnClickedFlatShadingButton)
    ON_BN_CLICKED(IDC_GOURAUD_SHADING_BUTTON, &CBasicFunctionsDlg::OnBnClickedGouraudShadingButton)
    ON_BN_CLICKED(IDC_USER_VIEW_SELECTED_CHECK, &CBasicFunctionsDlg::OnBnClickedUserViewSelectedCheck)
    ON_BN_CLICKED(IDC_RESET_CAMERA_ROTATION_BUTTON, &CBasicFunctionsDlg::OnBnClickedResetCameraRotationButton)
    ON_BN_CLICKED(IDC_DRAW_TEXTURE_CHECK, &CBasicFunctionsDlg::OnBnClickedDrawTextureCheck)
END_MESSAGE_MAP()


// CBasicFunctionsDlg �޽��� ó����

BOOL CBasicFunctionsDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// �ý��� �޴��� "����..." �޴� �׸��� �߰��մϴ�.

	// IDM_ABOUTBOX�� �ý��� ��� ������ �־�� �մϴ�.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// �� ��ȭ ������ �������� �����մϴ�. ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.
    
    RECT rect;
    displayPanel_.GetWindowRect(&rect);
    ScreenToClient(&rect);
    openGlPanel_.Create(rect, this);
    
    InitializeWorld();
    InitializeControls();

	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
}

void CBasicFunctionsDlg::InitializeWorld()
{
    World().ResizePinCount(10);

	if(!World().GetBall().Load(L"bowling_ball.obj", L"green_ball_skin.bmp"))
    {
        MessageBox(L"bowling_ball.obj doesn't exist. Please restart this application ^^;;");
    }
	World().GetBall().TranslateMore(6.0, -0.8, 1.0);
	
	if(!World().GetPin(0).Load(L"bowling_pin.obj", L""))
    {
        MessageBox(L"bowling_pin.obj doesn't exist. Please restart this application ^^;;");
    }

	World().GetPin(0).TranslateMore(-2.0, -0.0, 0.0);
	World().GetPin(0).ScaleRate(1.5, 1.5, 1.5);
	World().GetPin(0).CopyTo(World().GetPin(1));
	World().GetPin(1).TranslateMore(-2.6, 0.0, 0.5);
	World().GetPin(1).ScaleRate(1.5, 1.5, 1.5);
	World().GetPin(1).SetDrawTexture(false);
	World().GetPin(0).CopyTo(World().GetPin(2));
	World().GetPin(2).TranslateMore(-2.6, 0.0, -0.5);
	World().GetPin(2).ScaleRate(1.5, 1.5, 1.5);
	World().GetPin(2).SetDrawTexture(false);

	World().GetPin(0).CopyTo(World().GetPin(3));
	World().GetPin(3).TranslateMore(-3.2, 0.0, 1.0);
	World().GetPin(3).ScaleRate(1.5, 1.5, 1.5);
	World().GetPin(3).SetDrawTexture(false);
	World().GetPin(0).CopyTo(World().GetPin(4));
	World().GetPin(4).TranslateMore(-3.2, 0, 0.0);
	World().GetPin(4).ScaleRate(1.5, 1.5, 1.5);
	World().GetPin(4).SetDrawTexture(false);
	World().GetPin(0).CopyTo(World().GetPin(5));
	World().GetPin(5).TranslateMore(-3.2, 0.0, -1.0);
	World().GetPin(5).ScaleRate(1.5, 1.5, 1.5);
	World().GetPin(5).SetDrawTexture(false);

	World().GetPin(0).CopyTo(World().GetPin(6));
	World().GetPin(6).TranslateMore(-3.8, 0.0, 1.5);
	World().GetPin(6).ScaleRate(1.5, 1.5, 1.5);
	World().GetPin(6).SetDrawTexture(false);
	World().GetPin(0).CopyTo(World().GetPin(7));
	World().GetPin(7).TranslateMore(-3.8, 0.0, 0.5);
	World().GetPin(7).ScaleRate(1.5, 1.5, 1.5);
	World().GetPin(7).SetDrawTexture(false);
	World().GetPin(0).CopyTo(World().GetPin(8));
	World().GetPin(8).TranslateMore(-3.8, 0.0, -0.5);
	World().GetPin(8).ScaleRate(1.5, 1.5, 1.5);
	World().GetPin(8).SetDrawTexture(true);
	World().GetPin(0).CopyTo(World().GetPin(9));
	World().GetPin(9).TranslateMore(-3.8, 0.0, -1.5);
	World().GetPin(9).ScaleRate(1.5, 1.5, 1.5);
	World().GetPin(9).SetDrawTexture(false);

    // The Main Light
    World().GetLight().MoveTo(1.0, 1.0, 1.0);
    World().GetLight().Enable();
}

void CBasicFunctionsDlg::InitializeControls()
{
    scaleXEdit_.SetWindowText(L"1.0");
    scaleYEdit_.SetWindowText(L"1.0");
    scaleZEdit_.SetWindowText(L"1.0");

    cameraLocationXEdit_.SetWindowText(L"0.0");
    cameraLocationYEdit_.SetWindowText(L"0.0");
    cameraLocationZEdit_.SetWindowText(L"10.0");
    
    cameraLookAtXEdit_.SetWindowText(L"0.0");
    cameraLookAtYEdit_.SetWindowText(L"0.0");
    cameraLookAtZEdit_.SetWindowText(L"0.0");

    cameraUpXEdit_.SetWindowText(L"0.0");
    cameraUpYEdit_.SetWindowText(L"1.0");
    cameraUpZEdit_.SetWindowText(L"0.0");

    // Speed Slider
    speedSlider_.SetRange(1, 2000);
    speedSlider_.SetRangeMin(1);
    speedSlider_.SetRangeMax(2000);
    speedSlider_.SetPos(100);

    ambientREdit_.SetWindowText(L"0.5");
    ambientGEdit_.SetWindowText(L"0.5");
    ambientBEdit_.SetWindowText(L"0.5");
    diffuseREdit_.SetWindowText(L"1.0");
    diffuseGEdit_.SetWindowText(L"1.0");
    diffuseBEdit_.SetWindowText(L"1.0");
    specularREdit_.SetWindowText(L"0.5");
    specularGEdit_.SetWindowText(L"0.5");
    specularBEdit_.SetWindowText(L"0.5");

    userViewSelectedCheck_.SetCheck(TRUE);
    openGlPanel_.SetManipulatingSprite(true);
    lightCheck_.SetCheck(TRUE);
    Lighting().EnableLighting();
    drawTextureCheck_.SetCheck(TRUE);
}

void CBasicFunctionsDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�. ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CBasicFunctionsDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ�Դϴ�.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Ŭ���̾�Ʈ �簢������ �������� ����� ����ϴ�.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �������� �׸��ϴ�.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�.
HCURSOR CBasicFunctionsDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



BOOL CBasicFunctionsDlg::OnEraseBkgnd(CDC* pDC)
{
    // TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

    return CDialogEx::OnEraseBkgnd(pDC);
}


void CBasicFunctionsDlg::OnSize(UINT nType, int cx, int cy)
{
    CDialogEx::OnSize(nType, cx, cy);
}

void CBasicFunctionsDlg::UpdateAndDraw()
{
    //static float lastTime = (float)timeGetTime();
    //float currTime = (float)timeGetTime();
    //float timeDelta = (currTime - lastTime)/0.001f;
    //lastTime = currTime;

    //CString fpsText;
    //if(timeDelta != 0.0)
    //{
    //    fpsText.Format(L"%d", (int)(double)1000.0f/timeDelta);
    //    fpsStatic_.SetWindowText(fpsText);
    //}
    const float Speed = static_cast<float>(speedSlider_.GetPos() / 100.0);

    const float MoveUnit = 0.01 * Speed;
    const float RotateUnit = 0.5 * Speed;
    const float ScaleRate = 0.01 * Speed;

    float moveX = 0.0;
    float moveY = 0.0;
    float moveZ = 0.0;

    float rotateXAngle = 0.0;
    float rotateYAngle = 0.0;
    float rotateZAngle = 0.0;

    float magnitudeRate = 1.0;

    if(moveLeftButtonDown_)
    {   
        moveX = -MoveUnit;
    }
    else if(moveRightButtonDown_)
    {
        moveX = MoveUnit;
    }

    if(moveUpButtonDown_)
    {   
        moveY = MoveUnit;
    }
    else if(moveDownButtonDown_)
    {
        moveY = -MoveUnit;
    }

    if(moveFarButtonDown_)
    {   
        moveZ = -MoveUnit;
    }
    else if(moveNearButtonDown_)
    {
        moveZ = MoveUnit;
    }



    if(rotateUpButtonDown_)
    {   
        rotateXAngle = -RotateUnit;
    }
    else if(rotateDownButtonDown_)
    {
        rotateXAngle = RotateUnit;
    }

    if(rotateLeftButtonDown_)
    {   
        rotateYAngle = -RotateUnit;
    }
    else if(rotateRightButtonDown_)
    {
        rotateYAngle = RotateUnit;
    }

    if(rollLeftButtonDown_)
    {   
        rotateZAngle = RotateUnit;
    }
    else if(rollRightButtonDown_)
    {
        rotateZAngle = -RotateUnit;
    }

    if(biggerButtonDown_)
    {
        magnitudeRate += ScaleRate;
    }
    else if(smallerButtonDown_)
    {
        magnitudeRate -= ScaleRate;
    }

	World().GetBall().TranslateMore(moveX, moveY, moveZ);
    World().GetBall().RotateXMore(rotateXAngle);
    World().GetBall().RotateYMore(rotateYAngle);
    World().GetBall().RotateZMore(rotateZAngle);
    World().GetBall().ScaleRate(magnitudeRate, magnitudeRate, magnitudeRate);

	World().GetBall2().TranslateMore(moveX, moveY, moveZ);
    World().GetBall2().RotateXMore(rotateXAngle);
    World().GetBall2().RotateYMore(rotateYAngle);
    World().GetBall2().RotateZMore(rotateZAngle);
    World().GetBall2().ScaleRate(magnitudeRate, magnitudeRate, magnitudeRate);

    Vector3 values;
    Vector3 values2;

    // Scaling
    values.X = ToFloat(scaleXEdit_);
    values.Y = ToFloat(scaleYEdit_);
    values.Z = ToFloat(scaleZEdit_);
    GetSelectedSprite().Scale(values.X, values.Y, values.Z);

    //
    // Camera
    //
    if(cameraAutoRotateCheck_.GetCheck())
    {
        World().GetCamera().RotateYMore(RotateUnit);
    }

    values.X = ToFloat(cameraLocationXEdit_);
    values.Y = ToFloat(cameraLocationYEdit_);
    values.Z = ToFloat(cameraLocationZEdit_);
    World().GetCamera().MoveTo(values.X, values.Y, values.Z);

    values.X = ToFloat(cameraLookAtXEdit_);
    values.Y = ToFloat(cameraLookAtYEdit_);
    values.Z = ToFloat(cameraLookAtZEdit_);
    World().GetCamera().LookAt(values.X, values.Y, values.Z);

    values.X = ToFloat(cameraUpXEdit_);
    values.Y = ToFloat(cameraUpYEdit_);
    values.Z = ToFloat(cameraUpZEdit_);
    World().GetCamera().SetUpVector(values.X, values.Y, values.Z);

    World().GetCamera().Apply();

    // 
    // Light
    //
    World().GetLight().SetAmbient(ToFloat(ambientREdit_), ToFloat(ambientGEdit_), ToFloat(ambientBEdit_));
    World().GetLight().SetDiffuse(ToFloat(diffuseREdit_), ToFloat(diffuseGEdit_), ToFloat(diffuseBEdit_));
    World().GetLight().SetSpecular(ToFloat(specularREdit_), ToFloat(specularGEdit_), ToFloat(specularBEdit_));

    openGlPanel_.Invalidate();
}



BOOL CBasicFunctionsDlg::DestroyWindow() 
{
    // TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
    return CDialogEx::DestroyWindow();
}


void CBasicFunctionsDlg::OnDestroy()
{
    CDialogEx::OnDestroy();
    // TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
}


void CBasicFunctionsDlg::OnOK()
{
    DestroyWindow();
}


void CBasicFunctionsDlg::OnCancel()
{
    DestroyWindow();
}


void CBasicFunctionsDlg::OnBnClickedRotateLeftButton()
{
    
}


BOOL CBasicFunctionsDlg::PreTranslateMessage(MSG* pMsg)
{
    struct ButtonDownStatus
    {
        CWnd* control;
        bool* isButtonDown;
    };

    static ButtonDownStatus buttonDownStatus[] =
    {
        { &rotateLeftButton_, &rotateLeftButtonDown_ },
        { &rotateRightButton_, &rotateRightButtonDown_ },
        { &rotateUpButton_, &rotateUpButtonDown_ },
        { &rotateDownButton_, &rotateDownButtonDown_ },
        { &rollLeftButton_, &rollLeftButtonDown_ },
        { &rollRightButton_, &rollRightButtonDown_ },
        { &moveLeftButton_, &moveLeftButtonDown_ },
        { &moveRightButton_, &moveRightButtonDown_ },
        { &moveUpButton_, &moveUpButtonDown_ },
        { &moveDownButton_, &moveDownButtonDown_ },
        { &moveFarButton_, &moveFarButtonDown_ },
        { &moveNearButton_, &moveNearButtonDown_ },
        { &biggerButton_, &biggerButtonDown_ },
        { &smallerButton_, &smallerButtonDown_ }
    };

    switch(pMsg->message)
    {
    case WM_LBUTTONDOWN:
    case WM_LBUTTONUP:
        bool isButtonDown = pMsg->message == WM_LBUTTONDOWN;

        for(int i = 0; i < sizeof(buttonDownStatus)/sizeof(ButtonDownStatus); ++i)
        {
            if(pMsg->hwnd == buttonDownStatus[i].control->m_hWnd)
            {
                *buttonDownStatus[i].isButtonDown = isButtonDown;
                break;
            }
        }
/*
        if(pMsg->hwnd == rotateLeftButton_.m_hWnd)
        {
            rotateLeftButtonDown_ = isButtonDown;
        }
        else if(pMsg->hwnd == rotateRightButton_.m_hWnd)
        {
            rotateRightButtonDown_ = isButtonDown;
        }
        else if(pMsg->hwnd == rotateUpButton_.m_hWnd)
        {
            rotateUpButtonDown_ = isButtonDown;
        }
        else if(pMsg->hwnd == rotateDownButton_.m_hWnd)
        {
            rotateDownButtonDown_ = isButtonDown;
        }
        else if(pMsg->hwnd == rollLeftButton_.m_hWnd)
        {
            rollLeftButtonDown_ = isButtonDown;
        }
        else if(pMsg->hwnd == rollLeftButton_.m_hWnd)
        {
            rollRightButtonDown_ = isButtonDown;
        }
        */
        break;

    }

    return CDialogEx::PreTranslateMessage(pMsg);
}


void CBasicFunctionsDlg::OnBnClickedResetSpriteButton()
{
    World().GetBall().Reset();
    World().GetBall2().Reset();
}


//void CBasicFunctionsDlg::OnEnChangeScaleXEdit()
//{
//    // TODO:  RICHEDIT ��Ʈ���� ���, �� ��Ʈ����
//    // CDialogEx::OnInitDialog() �Լ��� ������ 
//    //�ϰ� ����ũ�� OR �����Ͽ� ������ ENM_CHANGE �÷��׸� �����Ͽ� CRichEditCtrl().SetEventMask()�� ȣ������ ������
//    // �� �˸� �޽����� ������ �ʽ��ϴ�.
//
//    UpdateAndDraw();
//}

float CBasicFunctionsDlg::ToFloat(const CWnd& wnd)
{
    CString text;
    float value;
    wnd.GetWindowText(text);
    swscanf(text, L"%f", &value);
    return value;
}


void CBasicFunctionsDlg::OnEditChange()
{
    UpdateAndDraw();
}


void CBasicFunctionsDlg::OnBnClickedTestButton()
{
    //World().GetBall().Load(L"HappyBuddha.obj");
    CFileDialog fileDialog(TRUE, L"obj", NULL, OFN_FILEMUSTEXIST | OFN_LONGNAMES, L"Object (*.obj) | *.obj", this);
    INT_PTR result = fileDialog.DoModal();
    if(result == IDOK)
    {
        CString pathName = fileDialog.GetPathName();
        MessageBox(pathName);
    }
}


void CBasicFunctionsDlg::OnBnClickedDrawNormalCheck()
{
    World().GetBall().SetDrawNormal(drawNormalCheck_.GetCheck() != 0);
}


void CBasicFunctionsDlg::OnBnClickedMeshPointButton()
{
    World().GetBall().SetMeshMode(MeshMode_Point);
    World().GetBall2().SetMeshMode(MeshMode_Point);
}


void CBasicFunctionsDlg::OnBnClickedMeshWireframeButton()
{
    World().GetBall().SetMeshMode(MeshMode_Wireframe);
    World().GetBall2().SetMeshMode(MeshMode_Wireframe);
}


void CBasicFunctionsDlg::OnBnClickedMeshQuadButton()
{
    World().GetBall().SetMeshMode(MeshMode_QuadMesh);
    World().GetBall2().SetMeshMode(MeshMode_QuadMesh);
}


void CBasicFunctionsDlg::OnNMReleasedcaptureSpeedSlider(NMHDR *pNMHDR, LRESULT *pResult)
{
    *pResult = 0;
}


BOOL CBasicFunctionsDlg::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
    GetSelectedSprite().TranslateMore(0.0, 0.0, zDelta/240.0);

    return CDialogEx::OnMouseWheel(nFlags, zDelta, pt);
}


void CBasicFunctionsDlg::OnBnClickedCameraAutoRotationCheck()
{
}


void CBasicFunctionsDlg::OnBnClickedLightCheck()
{
    Lighting lighting;
    if(lightCheck_.GetCheck())
    {
        lighting.EnableLighting();
    }
    else
    {
        lighting.DisableLighting();
    }
}


void CBasicFunctionsDlg::OnBnClickedFlatShadingButton()
{
    Lighting lighting;
    lighting.SetShadeModelFlat();
}


void CBasicFunctionsDlg::OnBnClickedGouraudShadingButton()
{
    Lighting lighting;
    lighting.SetShadeModelSmooth();
}

Virgin::Sprite& CBasicFunctionsDlg::GetSelectedSprite()
{
    if(userViewSelectedCheck_.GetCheck())
    {
        return World().GetBall();
    }
    else
    {
        return World().GetBall2();
    }
}


void CBasicFunctionsDlg::OnBnClickedUserViewSelectedCheck()
{
    if(userViewSelectedCheck_.GetCheck())
    {
        openGlPanel_.SetManipulatingSprite(true);
    }
    else
    {
        openGlPanel_.SetManipulatingSprite(false);
    }
}


void CBasicFunctionsDlg::OnBnClickedResetCameraRotationButton()
{
    World().GetCamera().ResetRotation();
}


void CBasicFunctionsDlg::OnBnClickedDrawTextureCheck()
{
    if(drawTextureCheck_.GetCheck())
    {
        World().GetBall().SetDrawTexture(true);
        World().GetBall2().SetDrawTexture(true);
    }
    else
    {
        World().GetBall().SetDrawTexture(false);
        World().GetBall2().SetDrawTexture(false);
    }
}

// World Instance �� �� ª�� �ڵ�� ���� �� �ֵ���
World& CBasicFunctionsDlg::World()
{
    return World::Instance();
}
