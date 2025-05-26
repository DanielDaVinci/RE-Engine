#include "RCameraLegacy.h"

#include "ThirdParty/ExternalIncludes/GLM/ext/matrix_clip_space.hpp"
#include "ThirdParty/ExternalIncludes/GLM/ext/matrix_transform.hpp"
#include "ThirdParty/ExternalIncludes/GLM/gtx/extended_min_max.hpp"

RCameraLegacy::RCameraLegacy(GLuint screenWidth, GLuint screenHeight, GLfloat FOV, glm::vec3 position, glm::vec3 angle)
{
	setScreenWidth(screenWidth);
	setScreenHeight(screenHeight);

	setFOV(FOV);

	setPosition(position);
	setAngle(angle);
	scale = { 1.0f, 1.0f, 1.0f};
}

void RCameraLegacy::setPosition(glm::vec3 position)
{
	this->position = position;
}

glm::vec3 RCameraLegacy::getPosition()
{
	return position;
}

void RCameraLegacy::setX(GLfloat x)
{
	this->position.x = x;
}

GLfloat RCameraLegacy::getX()
{
	return this->position.x;
}

void RCameraLegacy::setY(GLfloat y)
{
	this->position.y = y;
}

GLfloat RCameraLegacy::getY()
{
	return this->position.y;
}

void RCameraLegacy::setZ(GLfloat z)
{
	this->position.z = z;
}

GLfloat RCameraLegacy::getZ()
{
	return this->position.z;
}

void RCameraLegacy::setAngle(glm::vec3 angle)
{
	this->angle = angle;
}

glm::vec3 RCameraLegacy::getAngle()
{
	return angle;
}

void RCameraLegacy::setPitch(GLfloat angle)
{
	this->angle.x = angle;
}

GLfloat RCameraLegacy::getPitch()
{
	return angle.x;
}

void RCameraLegacy::setYaw(GLfloat angle)
{
	this->angle.y = angle;
}

GLfloat RCameraLegacy::getYaw()
{
	return angle.y;
}

void RCameraLegacy::setRoll(GLfloat angle)
{
	this->angle.z = angle;
}

GLfloat RCameraLegacy::getRoll()
{
	return angle.z;
}

void RCameraLegacy::setScale(glm::vec3 scale)
{
	this->scale = scale;
}

glm::vec3 RCameraLegacy::getScale()
{
	return scale;
}

void RCameraLegacy::setFOV(GLfloat FOV)
{
	this->FOV = glm::max(glm::min(FOV, 179.99f), 0.001f);
}

GLfloat RCameraLegacy::getFOV()
{
	return FOV;
}

void RCameraLegacy::setScreenWidth(GLuint screenWidth)
{
	this->screenWidth = screenWidth;
}

GLuint RCameraLegacy::getScreenWidth()
{
	return screenWidth;
}

void RCameraLegacy::setScreenHeight(GLuint screenHeight)
{
	this->screenHeight = screenHeight;
}

GLuint RCameraLegacy::getScreenHeight()
{
	return screenHeight;
}

glm::mat4 RCameraLegacy::getViewMatrix()
{
	return glm::lookAt(getPosition(), getPosition() + getFrontDirection(), getUpDirection());
}

glm::mat4 RCameraLegacy::getProjectionMatrix()
{
	return glm::perspective(glm::radians(FOV), (GLfloat)screenWidth/screenHeight, 0.01f, 100.0f);
}

glm::vec3 RCameraLegacy::getFrontDirection()
{
	glm::vec3 direction;

	direction.x = glm::cos(glm::radians(angle.x)) * glm::cos(glm::radians(angle.y));
	direction.y = glm::cos(glm::radians(angle.x)) * glm::sin(glm::radians(angle.y));
	direction.z = glm::sin(glm::radians(angle.x));

	return direction;
}

glm::vec3 RCameraLegacy::getUpDirection()
{
	return glm::cross(getRightDirection(), getFrontDirection());
}

glm::vec3 RCameraLegacy::getRightDirection()
{
	return glm::cross(getFrontDirection(), { 0.0f, 0.0f, 1.0f });
}
