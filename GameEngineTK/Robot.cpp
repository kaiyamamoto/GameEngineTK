// 
// Robot�̃N���X
// K.Yamamoto
// 

#include "Robot.h"
#include"State\OnGroundState.h"
#include "State\JumpingState.h"
#include "State\InAirState.h"

// ���O���
using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// �R���X�g���N�^
/// </summary>
Robot::Robot()
	:Object3D()
	,m_robotParts(Parts::length)
	,m_state(OnGroundState::GetInstance())	// ������Ԍ�ŕύX
	,m_speed(Vector3(0.0f,0.0f,0.0f))
	,m_acceleSpeed(Vector3(0.0f,0.05f,0.0f))
	, m_autoRun(false)
{
	// ������
	Initialize();
}

// ������
void Robot::Initialize()
{
	// �I�u�W�F�N�g�̓ǂݍ���
	m_robotParts[BODY] = std::make_unique<Object3D>(L"Resources\\body.cmo");
	m_robotParts[HEAD] = std::make_unique<Object3D>(L"Resources\\head.cmo");
	m_robotParts[RIGHTARM] = std::make_unique<Object3D>(L"Resources\\missile.cmo");
	m_robotParts[LEFTARM] = std::make_unique<Object3D>(L"Resources\\missile.cmo");
	m_robotParts[RIGHTLEG] = std::make_unique<Object3D>(L"Resources\\leg.cmo");
	m_robotParts[LEFTLEG] = std::make_unique<Object3D>(L"Resources\\leg.cmo");

	// �e�q�֌W
	// �S�p�[�cBODY�̎q�ɂȂ�
	m_robotParts[BODY]->SetParent(this);
	m_robotParts[HEAD]->SetParent(m_robotParts[BODY].get());
	m_robotParts[RIGHTARM]->SetParent(m_robotParts[BODY].get());
	m_robotParts[LEFTARM]->SetParent(m_robotParts[BODY].get());
	m_robotParts[RIGHTLEG]->SetParent(m_robotParts[BODY].get());
	m_robotParts[LEFTLEG]->SetParent(m_robotParts[BODY].get());

	// �T�C�Y�ݒ�
	this->SetScale(0.5f);

	// �S�̓I�ȍ��W����
	m_robotParts[HEAD]->SetPosition(Vector3(0.0f, 3.0f, 0.0f));
	m_robotParts[RIGHTARM]->SetPosition(Vector3(2.0f, 2.0f, 0.0f));
	m_robotParts[LEFTARM]->SetPosition(Vector3(-2.0f, 2.0f, 0.0f));
	m_robotParts[RIGHTLEG]->SetPosition(Vector3(1.0f, 0.0f, 0.0f));
	m_robotParts[LEFTLEG]->SetPosition(Vector3(-1.0f, 0.0f, 0.0f));
}

/// <summary>
/// �`��
/// </summary>
/// <param name="state"></param>
/// <param name="view"></param>
/// <param name="proj"></param>
void Robot::Draw(const DirectX::CommonStates & state, const DirectX::SimpleMath::Matrix & view, const DirectX::SimpleMath::Matrix & proj) const
{
	// �p�[�c�̕`��
	for (auto itr = m_robotParts.begin(); itr != m_robotParts.end(); ++itr) {
		(*itr)->Draw(state, view, proj);
	}
}

/// <summary>
/// �X�V
/// </summary>
void Robot::Update()
{
	// ���̍X�V
	this->Object3D::Update();

	// ��]�ړ�
	Vector3 move = m_speed;
	Matrix rotmat = Matrix::Identity;
	rotmat *= Matrix::CreateRotationY(GetEulerAngleRadians().y);
	move = Vector3::TransformNormal(move, rotmat);
	m_position += move;

	// �s��X�V
	Calc();
}

/// <summary>
/// �s��̍X�V
/// </summary>
void Robot::Calc()
{
	// ���N���X�̍s��X�V
	this->Object3D::Calc();
	// �p�[�c�̍s��X�V
	for (auto itr = m_robotParts.begin(); itr != m_robotParts.end(); ++itr){
		(*itr)->Calc();
	}
}

// �����蔻�菈��
RobotState * Robot::CollisionCheck()
{
	std::vector<std::shared_ptr<LandShape>> landshape = m_pStage->GetLandshape();
	
	// �������������蔻��
	{
		Sphere sphere = GetCollisionNodeBody();
		Vector3 trans = GetPosition();
		Vector3 sphere2player = trans - sphere.center;

		const int REPEAT_LIMIT = 5;

		int rejectNum = 0;

		for (std::vector<std::shared_ptr<LandShape>>::iterator it = landshape.begin();
			it != landshape.end();
			)
		{
			const LandShape* pLandShape = it->get();

			Vector3 reject;	// �r�˃x�N�g�������邽�߂̕ϐ�

			if (pLandShape->IntersectSphere(sphere, &reject))
			{
				// �߂荞�ݕ������A���������o���悤�Ɉړ�
				sphere.center = sphere.center + reject;
				if (++rejectNum >= REPEAT_LIMIT)
				{
					break;
				}
				it = landshape.begin();
			}
			else
			{
				it++;
			}
		}

		SetPositionX(sphere.center.x + sphere2player.x);
		SetPositionZ(sphere.center.z + sphere2player.z);

		Calc();
	}

	// ���������n�`�����蔻��
	{
		const Vector3& vel = GetSpeed();

		// ���x��������łȂ��H
		if (vel.y <= 0.0f)
		{
			bool hit = false;
			Segment player_segment;
			Vector3 player_pos = GetPosition();
			player_segment.start = player_pos + Vector3(0, SEGMENT_LENGTH, 0);
			// �e�̈ʒu�����o���邽�߁A�������牺�����ɗ]�T�������Ĕ�������
			player_segment.end = player_pos + Vector3(0, -SHADOW_DISTANCE, 0);

			// �傫�������ŏ�����
			float distance = 1.0e5;
			Vector3 inter;

			for (std::vector<std::shared_ptr<LandShape>>::iterator it = landshape.begin();
				it != landshape.end();
				it++)
			{
				const LandShape* pLandShape = it->get();
				float temp_distance;
				Vector3 temp_inter;

				// ���ʂƂ̓�����𔻒�
				if (pLandShape->IntersectSegmentFloor(player_segment, &temp_inter))
				{
					hit = true;
					temp_distance = Vector3::Distance(player_segment.start, temp_inter);
					if (temp_distance < distance)
					{
						inter = temp_inter;
						distance = temp_distance;
					}
					// ���[�v������
					goto BREAK;
				}
			}
		BREAK:

			bool landing = false;

			// �q�b�g
			if (hit)
			{
				// �z�������͈͓̔����H
				if (distance <= SEGMENT_LENGTH + ADSORP_LENGTH)
				{
					// ���n
					landing = true;
					Vector3 new_position = player_pos;
					// �߂肱�ނ���グ��
					inter.y += 1.0f;
					new_position.y = inter.y;
					SetPositionY(new_position.y);
					// �n�ʂɒ���
					return OnGroundState::GetInstance();
				}
			}

			// ���n�łȂ����
			if (!landing && !hit)
			{// �����J�n
				if ((m_state != InAirState::GetInstance()))
					return InAirState::GetInstance();
			}
			Calc();
		}
	}

	return nullptr;
}
