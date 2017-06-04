void median_blur(Mat im) {
	int nl = im.rows, nc = im.cols*im.channels();

	for (int j = 0;j < nl;j++) {
		uchar *pre = nullptr, *data = nullptr, *next = nullptr;
		if (j - 1 > 0)
			pre = im.ptr<uchar>(j - 1);
		data = im.ptr<uchar>(j);
		if (j + 1 < nl)
			next = im.ptr<uchar>(j + 1);

		for (int i = 0;i < nc;i += 3) {
			if (IsSaltOrPepper(&data[i])) {
				for (int channel = 0;channel < 3;channel++) {
					int arr[9] = { 0 }, count = 0;
					if (pre != nullptr) {
						for (int k = -1;k <= 1;k++)
							arr[count++] = pre[channel + i + 3 * k];
					}

					for (int k = -1;k <= 1;k++)
						arr[count++] = data[channel + i + 3 * k];

					if (next != nullptr) {
						for (int k = -1;k <= 1;k++)
							arr[count++] = next[channel + i + 3 * k];
					}

					sort(arr, arr + count);
					data[i + channel] = arr[count / 2];
				}
			}
		}
	}
}
void blur(Mat im) {
	int nl = im.rows, nc = im.cols*im.channels();

	for (int j = 0;j < nl;j++) {

		uchar *pre = nullptr, *data = nullptr, *next = nullptr;
		if (j - 1 > 0)
			pre = im.ptr<uchar>(j - 1);
		data = im.ptr<uchar>(j);
		if (j + 1 < nl)
			next = im.ptr<uchar>(j + 1);

		for (int i = 0;i < nc;i += 3) {
			if (IsSaltOrPepper(&data[i])) {
				for (int channel = 0;channel < im.channels();channel++) {
					int	sum = 0, count = 0;
					if (pre != nullptr) {
						sum += pre[channel + i - 3] + pre[channel + i] + pre[channel + i + 3];
						count += 3;
					}
					sum += data[channel + i - 3] + data[channel + i] + data[channel + i + 3];
					count += 3;
					if (next != nullptr) {
						sum += next[channel + i - 3] + next[channel + i] + next[channel + i + 3];
						count += 3;
					}
					data[i + channel] = sum / count;
				}
			}
		}
	}
}