// SceneCollision.h

#pragma once

class Collider;
class Scene;
class UIWidget;
class UIWindow;


class SceneCollision
{
public:
	/* 충돌 체크 */
	void collision();
	void collisionMouse();

	/* 충돌체 중인 개체 추가 */
	void addCollider(Collider* _pCollider);
	void addUIWindow(UIWindow* _pWindow);

	UIWidget* getSelectedWidget() { return m_pSelectedWidget; }
	void setSelectedWidget(UIWidget* _pWidget) { m_pSelectedWidget = _pWidget; }

	void clearMouseCollision(Collider* _pCollider)
	{
		if (_pCollider == m_pMouseCollision)
		{
			m_pMouseCollision = nullptr;
		}
	}

private:
	Scene*				m_pOwnerScene;
	vector<Collider*>	m_vecCollider;
	vector<UIWindow*>	m_vecUIWindow;
	UIWidget*			m_pMouseHoveredWidget;
	UIWidget*			m_pSelectedWidget;
	Collider*			m_pMouseCollision;

	SceneCollision();
	virtual ~SceneCollision();

	static int sortY(const void* _pSrc, const void* _pDes);

	friend class Scene;
};

