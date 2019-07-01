#include "3d_baseLine_predictor.h"


BaseLinePredictor::BaseLinePredictor(const string& model_path)
{
	tensorflow::SessionOptions options;
	options.config.mutable_gpu_options()->set_per_process_gpu_memory_fraction(0.3);
	options.config.mutable_gpu_options()->set_allow_growth(true);
	Status status = NewSession(options, &session);
	if (!status.ok()) {
		is_opened = false;
	}
	else
	{
		if (0 != model.load(session, model_path)) {
			is_opened = false;
		}
		else 
		{
			is_opened = true;
		}


	}
}

int BaseLinePredictor::predict(const std::vector<float>& input, std::vector<float>& output)
{
	tf_model::BaseLineFeatureAdapter input_feat;
	input_feat.assign(INPUT_NAME, input);
	input_feat.assign(DROPOUT_FLAG, dropout);
	input_feat.assign(IS_TRAINING, is_train);
	if (0 != model.predict(session, input_feat, OUTPUT_NAME, output)) {
		return -1;
	}
	return output.size();
}

bool BaseLinePredictor::isOpened()
{
	return is_opened;
}
