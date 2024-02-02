struct Calibration
{
	Calibration(float temperature, float voltage, float slope)
	{
		this->temperature = temperature;
		this->voltage = voltage;
		this->slope = slope;
	}

	float temperature;
	float voltage;
	float slope;
};

class Controller
{
	public:
		Controller(std::string fileNameCalibration);
		~Controller();
		float convertmVtoK(float voltage);
		float convertKtomV(float temperature);

	protected:
		void loadCalibrationTable(std::string fileName);
		Calibration findClosestCalibrationByV(float voltage);
		Calibration findClosestCalibrationByT(float temperature);
	private: 
		std::vector<Calibration> tableCalibrationSortedByV;
		std::vector<Calibration> tableCalibrationSortedByT;

		static bool compareCalibrationByV(Calibration c1, Calibration c2)
		{
			return (c1.voltage < c2.voltage);
		}

		static bool compareCalibrationByT(Calibration c1, Calibration c2)
		{
			return (c1.temperature < c2.temperature);
		}

		friend void printCalibrationTables(Controller *pCtrl);
};

/* Unit Tests */
void printCalibrationTables(Controller*);

