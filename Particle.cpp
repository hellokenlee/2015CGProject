#include "Particle.h"

void cSnow::init(){
	float zoom=0.0;
	float colors[3]={1,1,1};
	tex.loadTexture("snow.png");
	//��ʼ������ϵͳ
	for(int loop =0; loop<MAX_PARTICLE;loop++){
		particles[loop].active=true;
		particles[loop].life=2.0f;
		particles[loop].fade=float(rand()%100)/1000+0.003;

		particles[loop].xg=0.0f;						// ����X�᷽����ٶ�Ϊ0
		particles[loop].yg=-1.0f;						//  ����Y�᷽����ٶ�Ϊ-0.8
		particles[loop].zg=0.0f;						//  ����Z�᷽����ٶ�Ϊ0

	}
	pCamera=cCamera::getCamera();
}

void cSnow::render(){
	tex.bindTexutre();
	array<double,3> cPos=pCamera->getPosition();
	for (int loop=0;loop<MAX_PARTICLE;loop++) {
		if(particles[loop].active) {
			float x=cPos[0]+particles[loop].x;
			float y=cPos[1]+particles[loop].y;
			float z=cPos[2]+particles[loop].z;
			glColor4f(particles[loop].r,particles[loop].g,particles[loop].b,particles[loop].life);
			glBegin(GL_QUADS);{
				glTexCoord2f(0.0,0.0); 
				glVertex3f(x+halfParticleWidth,y+halfParticleHeight,z); 
				glTexCoord2f(1.0,0.0);
				glVertex3f(x-halfParticleWidth,y+halfParticleHeight,z); 
				glTexCoord2f(1.0,1.0); 
				glVertex3f(x-halfParticleWidth,y-halfParticleHeight,z); 
				glTexCoord2f(0.0,1.0); 
				glVertex3f(x+halfParticleWidth,y-halfParticleHeight,z); 
			}glEnd();

			particles[loop].x+=particles[loop].xi/(1000);	// ����X�����λ��
			particles[loop].y+=particles[loop].yi/(1000);	// ����Y�����λ��
			particles[loop].z+=particles[loop].zi/(1000);	// ����Z�����λ��

			particles[loop].xi+=particles[loop].xg;			// ����X�᷽���ٶȴ�С
			particles[loop].yi+=particles[loop].yg;			// ����Y�᷽���ٶȴ�С
			particles[loop].zi+=particles[loop].zg;			// ����Z�᷽���ٶȴ�С

			particles[loop].life-=particles[loop].fade;		// �������ӵ�����ֵ
			if(particles[loop].life<0.0){
				particles[loop].life=1.0;
				particles[loop].fade=float(rand()%100)/10000.0f+0.001f;			//�����ٶ�
				
				particles[loop].x=0.0f+(rand()%30-15.0);					    // �����ӳ���λ��
				particles[loop].y=20.0f;					
				particles[loop].z=0.0f+(rand()%30-15.0);

				particles[loop].xi=float((rand()%60)-32.0f);	// ������������ٶ�
				particles[loop].yi=float((rand()%60)-30.0f);	
				particles[loop].zi=float((rand()%60)-30.0f);

				particles[loop].r=1;		// ����������ɫ
				particles[loop].g=1;	
				particles[loop].b=1;
			}

		}
	}
}