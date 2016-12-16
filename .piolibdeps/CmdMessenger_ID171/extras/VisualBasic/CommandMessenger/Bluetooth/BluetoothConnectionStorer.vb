#Region "CmdMessenger - MIT - (c) 2014 Thijs Elenbaas."
'
'  CmdMessenger - library that provides command based messaging
'
'  Permission is hereby granted, free of charge, to any person obtaining
'  a copy of this software and associated documentation files (the
'  "Software"), to deal in the Software without restriction, including
'  without limitation the rights to use, copy, modify, merge, publish,
'  distribute, sublicense, and/or sell copies of the Software, and to
'  permit persons to whom the Software is furnished to do so, subject to
'  the following conditions:
'
'  The above copyright notice and this permission notice shall be
'  included in all copies or substantial portions of the Software.
'
'  Copyright 2014 - Thijs Elenbaas
'
#End Region


Imports Microsoft.VisualBasic
Imports System.IO
Imports System.Runtime.Serialization.Formatters.Binary

Namespace CommandMessenger.Bluetooth
	Public Class BluetoothConnectionStorer
		Implements IBluetoothConnectionStorer
		Private ReadOnly _settingsFileName As String
		''' <summary>
		''' Contructor of Store/Retreive object for SerialConnectionManagerSettings
		''' The file is serialized as a simple binary file
		''' </summary>
		Public Sub New()
			_settingsFileName = "BluetoothConnectionManagerSettings.cfg"
		End Sub

		''' <summary>
		''' Contructor of Store/Retreive object for SerialConnectionManagerSettings
		''' The file is serialized as a simple binary file
		''' </summary>
		''' <param name="settingsFileName">Filename of the settings file</param>
		Public Sub New(ByVal settingsFileName As String)
			_settingsFileName = settingsFileName
		End Sub

		''' <summary>
		''' Store SerialConnectionManagerSettings
		''' </summary>
		''' <param name="bluetoothConnectionManagerSettings">BluetoothConnectionManagerSettings</param>
		Public Sub StoreSettings(ByVal bluetoothConnectionManagerSettings As BluetoothConnectionManagerSettings) Implements IBluetoothConnectionStorer.StoreSettings
			Dim fileStream = File.Create(_settingsFileName)
			Dim serializer = New BinaryFormatter()
			serializer.Serialize(fileStream, bluetoothConnectionManagerSettings)
			fileStream.Close()
		End Sub

		''' <summary>
		''' Retreive SerialConnectionManagerSettings
		''' </summary>
		''' <returns>SerialConnectionManagerSettings</returns>
		Public Function RetrieveSettings() As BluetoothConnectionManagerSettings Implements IBluetoothConnectionStorer.RetrieveSettings
			Dim bluetoothConnectionManagerSettings = New BluetoothConnectionManagerSettings()
			If File.Exists(_settingsFileName) Then
				Dim fileStream = File.OpenRead(_settingsFileName)
				Dim deserializer = New BinaryFormatter()
				bluetoothConnectionManagerSettings = CType(deserializer.Deserialize(fileStream), BluetoothConnectionManagerSettings)
				fileStream.Close()
			End If
			Return bluetoothConnectionManagerSettings
		End Function
	End Class
End Namespace
