
#include "SimpleAnomalyDetector.h"
#define THRESHOLD 0.9

SimpleAnomalyDetector::SimpleAnomalyDetector() {
	// TODO Auto-generated constructor stub

}

SimpleAnomalyDetector::~SimpleAnomalyDetector() {
	// TODO Auto-generated destructor stub
}


void SimpleAnomalyDetector::learnNormal(const TimeSeries& ts){
	for (auto const& it1 : ts.getFeatureNames()) {
		string feature1 = it1;
		string feature2;
		// the current max correlation between two features.
		float curCor = 0;
		for (auto const& it2 : ts.getFeatureNames()) {
			if (it1 != it2) {
				// fill the arrays data from the timeseries vectors.
				auto value1 = ts.getValues(it1);
				auto value2 = ts.getValues(it2);
				float* x = new float[value1.size()];
				float* y = new float[value2.size()];
				for (int i = 0; i < value1.size(); ++i) {
					x[i] = value1[i];
					y[i] = value2[i];
				}
				float p = fabs(pearson(x, y, value1.size()));
				//if the pearson value is at least 0.9
				// and the pearson bigger then the last max correlation which checked.
				if (p >= THRESHOLD && p > curCor) {
					feature2 = it2;
					curCor = p;
				}
				delete [] x;
				delete [] y;
			}
		}
		// if there is a value in max
		if (curCor > 0) {
			// fill correlatedfeatures struct.
			correlatedFeatures corrF;
			corrF.feature1 = feature1;
			corrF.feature2 = feature2;
			corrF.corrlation = curCor;
			corrF.threshold = 0;
			int size = ts.getValues(it1).size;
			float* xPoints = new float[size];
			float* yPoints = new float[size];
			Point** totalPoints = new Point*[size];
			//create arrays to convert them to points.
			for (int j = 0; j < size; ++j) {
				xPoints[j] = ts.getValues(corrF.feature1)[j];
				yPoints[j] = ts.getValues(corrF.feature2)[j];
				totalPoints[j] = new Point(xPoints[j], yPoints[j]);
			}
			//create the line regression for this struct.
			corrF.lin_reg = linear_reg(totalPoints, size);
			// find the maximum deviation from the line.
			for (int i = 0; i < size; ++i) {
				Point p1(xPoints[i], yPoints[i]);
				float dev1 = dev(p1, corrF.lin_reg);
				if (dev1 > corrF.threshold) {
					corrF.threshold = dev1 * (float)THRESHOLD;
				}
			}
			//push the object that has made to threshold vector.
			this->cf.push_back(corrF);
			for (int j = 0; j < size; ++j)
			{
				delete[] totalPoints[j];
			}
			delete[] totalPoints;
			delete[] yPoints;
			delete[] xPoints;
		}
	}
}

vector<AnomalyReport> SimpleAnomalyDetector::detect(const TimeSeries& ts){
	vector<AnomalyReport> anomalyArray;
	for (correlatedFeatures corrF : cf)
	{
		int size = ts.getValues.size;
		string feat1 = corrF.feature1;
		string feat2 = corrF.feature2;
		for (int i = 0; i < size; i++)
		{
			// we now get the dev of every point and check whether it's an anomaly!
			Point currPoint(ts.getValues(feat1)[i], ts.getValues(feat2)[i]);
			float currPointDev = dev(currPoint, corrF.lin_reg);
			if (currPointDev > corrF.threshold)
			{
				//adding the point to the anomaly array via a new report
				AnomalyReport anomalyReport(feat1 + "-" + feat2, i + 1);
				anomalyArray.push_back(anomalyReport);
			}
		}
	}
	return anomalyArray;
}

