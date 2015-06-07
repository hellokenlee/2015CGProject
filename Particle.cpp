#include "Particle.h"

void cSnow::init(){
	float zoom=0.0;
	float colors[3]={1,1,1};
	tex.loadTexture("snow.png");
	//初始化粒子系统
	for(int loop =0; loop<MAX_PARTICLE;loop++){
		particles[loop].active=true;
		particles[loop].life=2.0f;
		particles[loop].fade=float(rand()%100)/1000+0.003;

		particles[loop].xg=0.0f;						// 设置X轴方向加速度为0
		particles[loop].yg=-1.0f;						//  设置Y轴方向加速度为-0.8
		particles[loop].zg=0.0f;						//  设置Z轴方向加速度为0

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

			particles[loop].x+=particles[loop].xi/(1000);	// 更新X坐标的位置
			particles[loop].y+=particles[loop].yi/(1000);	// 更新Y坐标的位置
			particles[loop].z+=particles[loop].zi/(1000);	// 更新Z坐标的位置

			particles[loop].xi+=particles[loop].xg;			// 更新X轴方向速度大小
			particles[loop].yi+=particles[loop].yg;			// 更新Y轴方向速度大小
			particles[loop].zi+=particles[loop].zg;			// 更新Z轴方向速度大小

			particles[loop].life-=particles[loop].fade;		// 减少粒子的生命值
			if(particles[loop].life<0.0){
				particles[loop].life=1.0;
				particles[loop].fade=float(rand()%100)/10000.0f+0.001f;			//消逝速度
				
				particles[loop].x=0.0f+(rand()%30-15.0);					    // 新粒子出现位置
				particles[loop].y=20.0f;					
				particles[loop].z=0.0f+(rand()%30-15.0);

				particles[loop].xi=float((rand()%60)-32.0f);	// 随机生成粒子速度
				particles[loop].yi=float((rand()%60)-30.0f);	
				particles[loop].zi=float((rand()%60)-30.0f);

				particles[loop].r=1;		// 设置粒子颜色
				particles[loop].g=1;	
				particles[loop].b=1;
			}

		}
	}
}