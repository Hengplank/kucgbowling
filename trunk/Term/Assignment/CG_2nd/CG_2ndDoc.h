
// CG_2ndDoc.h : CCG_2ndDoc Ŭ������ �������̽�
//


#pragma once

#include <string>
#include <locale.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

struct Vertex
{
	float x;
	float y;
	float z;
};

struct Face
{
	int vertex0;
	int vertex1;
	int vertex2;
	int vertex3;
};

class CCG_2ndDoc : public CDocument
{
protected: // serialization������ ��������ϴ�.
	CCG_2ndDoc();
	DECLARE_DYNCREATE(CCG_2ndDoc)

// Ư���Դϴ�.
public:

// �۾��Դϴ�.
public:

// �������Դϴ�.
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// �����Դϴ�.
public:
	virtual ~CCG_2ndDoc();
	void Initialize(CString);
	void PointDisplay();
	void WireframeDisplay();
	void QuadMeshDisplay(int);
	void DrawNormalVector();
	void TextureDisplay(int);
	void Tokenize(const string&, vector<int>&, const string&);
	void Destroy();
	void LoadTexture();
	void DisableTexture();
	void SetTextureFile(CString filePath);
private:
	void SetTotalCount();
	void SetModelFromFile();
	void SetNormalVector();
	Vertex GetOuterVector(Vertex, Vertex);
	float Magnitude(Vertex vector);
	int GetLineIndex(string value);
	void SetNormalElement(Vertex);
	void DrawVertex(int faceIndex, int shadingMode, bool isTexture);
// ����
private:
	enum Line {NONE = -1, VERTEX = 1, VERTEX_TEXTURE = 2, FACE = 3};
	Vertex *vertices, *tVertices;	// ����� ��, �ؽ��� ����� ��
	Face *faces, *tFaces;		// ���, �ؽ��� ���
	Vertex *fNVectors, *vNVectors;	// ����� ��������, ���� ��������
	CString filePath;
	int vertexCount, tVertexCount, faceCount;
	AUX_RGBImageRec *TextureImage[3];
	GLuint texture[1];
	CString texturePath;
public:
	enum Shading {NOTHING = -1, FLAT = 1, GOURAUD = 2};
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	DECLARE_MESSAGE_MAP()
};


template< typename To, typename From > 
const To StringCast(const From& from) 
{ 
	std::stringstream strStream;
	strStream << from; 
	To result; 
	strStream >> result; 
	if( strStream.fail() && !strStream.eof() ) return 0;   
	return result; 
}