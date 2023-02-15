int getNumberOfRooms() {
	int rooms;

	cout << "Enter the number of rooms to be painted: ";
	cin >> rooms;

	while (rooms < 1) {
		cout << "ERROR: Enter 1 or greater.\n";
		cout << "Enter the number of rooms to be painted.\n";
		cin >> rooms;
	}

	return rooms;
}