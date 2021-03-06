﻿// 사각 피스를 그리위해서 사용하는 Piece모델

#ifdef _WIN32
#define	WIN32_LEAN_AND_MEAN
#include <windows.h>
#endif

#include "ModelInterface.h"
#include <iostream>
#include <fstream>

#include "Md2Model.h"
#include "GameWorld.h"
#include "TextureManager.h"
#include "PieceModel.h"
//#include "GL/glew.h"


using std::cout;
using std::cerr;
using std::endl;


PieceModel::PieceModel(float Width,float Height) 
	: GameObejct(MARX_OBJECT_PIECEMODEL)
{
	m_Height = Height;
	m_Width = Width;
	_scale = 1.0f;
	x1 = m_Width ;
	y1 = m_Height;
	x2 = 0 ;
	y2 = 0;

}

void PieceModel::SetPieceSize(float Width,float Height)
{
	m_Height = Height;
	m_Width = Width;

	x1 = m_Width;
	y1 = m_Height;
	x2 = 0;
	y2 = 0;
}

bool PieceModel::loadTexture (const string &filename)
{
	// Get texture manager
	Texture2DManager *texMgr = Texture2DManager::getInstance ();

	// load the texture
	Texture2D *tex = texMgr->load (filename);

	if (!tex->fail ())
	{
		if(_skinIds.find(filename) == _skinIds.end())
			_skinIds.insert (SkinMap::value_type (filename, tex));
	}

	return (!tex->fail ());
}

bool PieceModel::loadTexture (const string &filename , const string &alphafilename)
{
	
	// Get texture manager
	Texture2DManager *texMgr = Texture2DManager::getInstance ();

	// load the texture
	Texture2D *tex = texMgr->load (filename,alphafilename);

	if (!tex->fail ())
	{
		if(_skinIds.find(filename + alphafilename) == _skinIds.end())
			_skinIds.insert (SkinMap::value_type (filename + alphafilename, tex));
	}

	return (!tex->fail ());
}


bool PieceModel::setTexture (const string &filename)
{
	SkinMap::iterator itor;
	itor = _skinIds.find (filename);

	if (itor != _skinIds.end ())
	{
		_tex = itor->second;
		return true;
	}
	else
	{
		_tex = NULL;
		return false;
	}
}

bool PieceModel::setTexture (const string &filename, const string &alphafilename)
{
	
	SkinMap::iterator itor;
	itor = _skinIds.find (filename + alphafilename);

	if (itor != _skinIds.end ())
	{
		_tex = itor->second;
		return true;
	}
	else
	{
		_tex = NULL;
		return false;
	}
	return true;
}

void PieceModel::renderFrameImmediate (int frame)
{
	RenderPiece();
}
void PieceModel::drawModelItpImmediate (int frameA, int frameB, float interp)
{
	RenderPiece();
}

void PieceModel::renderFrameWithGLcmds (int frame)
{
	RenderPiece();
}
void PieceModel::drawModelItpWithGLcmds (int frameA, int frameB, float interp)
{
	RenderPiece();
}

void PieceModel::RenderRect(float x, float y, int name)
{
	glPushName(name);
	float x1_ = x +  5;
	float y1_ = y + 5;
	float x2_ = x + (-1 * 5);
	float y2_ = y +  (-1 * 5);

	glColor4f(0.0f, 0.635f, 0.909f, 1.0f);
	glBegin(GL_TRIANGLE_STRIP);

	glVertex3f(x2_, y2_, 1);
	glVertex3f(x2_, y1_, 1);
	glVertex3f(x1_, y2_, 1);
	glVertex3f(x1_, y1_, 1);
	glEnd();
	

	

	glPopName();
}

void PieceModel::renderSelectFrameImmediate(int Numbers[])
{

	//glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_TEXTURE_2D);

	

	//
	glColor4f(0.0f, 0.635f, 0.909f,0.5f);
	glBegin(GL_LINES);

	glLineWidth(10);

	x1 = m_Width;
	y1 = m_Height;
	x2 = 0;
	y2 = 0;

	glVertex2f(x1,y1);
	glVertex2f(x2,y1);
	
	glVertex2f(x2,y1);
	glVertex2f(x2,y2);

	glVertex2f(x2,y2);
	glVertex2f(x1,y2);

	glVertex2f(x1,y2);
	glVertex2f(x1,y1);
	
	glDisable(GL_LINES);
	glColor3f(1.0f,1.0f,1.0f);
	glEnd();


	glColor4f(0.0f, 0.635f, 0.909f,0.2f);
	glBegin(GL_TRIANGLE_STRIP);

	glVertex3f(x2, y2, 0);
	glVertex3f(x2, y1, 0);
	glVertex3f(x1, y2, 0);
	glVertex3f(x1, y1, 0);



	//glDisable(GL_LINES);
	glEnd();

	//glPopName();
	glPushName(Numbers[8]);
	float pos[8][2] = { { 1,1 },{ 1,0 },{ 0,1 },{ 0,0 } ,{ 1, 0.5 } ,{ 0.5 , 1 } ,{ 0.5 , 0 } ,{ 0 , 0.5 } };

	for (int i = 0; i < 8; i++)
	{
		RenderRect(m_Width* pos[i][0], m_Height* pos[i][1], Numbers[i]);
	}
	glPopName();

	glColor3f(1.0f, 1.0f, 1.0f);
	glEnable(GL_TEXTURE_2D);



	
	
}

void PieceModel::RenderPiece()
{	
	// Bind to model's texture
	
	glDisable(GL_DEPTH_TEST);
	//glEnable(GL_BLEND);

	
	//glBlendFunc(GL_ONE_MINUS_DST_COLOR ,GL_ZERO);

	if (_tex) 
		_tex->bind ();
	

	glBegin(GL_TRIANGLE_STRIP); 

		glTexCoord2f(0,0); 
		glVertex3f(x2, y2,0); 

		glTexCoord2f(0,1);
		glVertex3f(x2, y1,0); 

		glTexCoord2f(1,0);
		glVertex3f(x1, y2,0);

		glTexCoord2f(1,1);
		glVertex3f(x1, y1,0);

		//glDisable(GL_LINES);
	glEnd();

	//glDisable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);

}

void PieceModel::RenderPiece(int value, int value2,int value3,int value4,int count)
{

}