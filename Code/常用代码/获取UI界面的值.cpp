        //获取UI界面的值
        PropertyList* angleDoubleProps = angleDouble->GetProperties();
        double creationAngle = angleDoubleProps->GetDouble("Value");
        delete angleDoubleProps;
        angleDoubleProps = NULL;



    
		//获取体
		PropertyList*  bodySelectProps = bodySelect->GetProperties();
		std::vector<NXOpen::TaggedObject *> bodys = bodySelectProps->GetTaggedObjectVector("SelectedObjects");
		delete bodySelectProps;
		bodySelectProps = NULL;
		  
		UF_initialize();
		UF_UI_open_listing_window();				//打开输出窗口
		char msg[256];
		for ( int i = 0; i < bodys.size(); ++i) 
		{
					tag_t bodyTAG=bodys[i]->Tag();
		sprintf(msg,"%d",bodyTAG);
		UF_UI_write_listing_window(msg);
		UF_UI_write_listing_window("\n");			//信息输出
			}

				UF_terminate();
		
		==============================================================
		//获取xxxx
		PropertyList*a = blockID->GetProperties();
		类型 b=a->getxxxx();
		delete a;
		a=NULL;