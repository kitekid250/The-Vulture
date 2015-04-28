Imports System.IO.Ports

Public Class Main

    ' the Serial port connected to the Arduino
    Dim port As New SerialPort
    Dim portList() As String

    Private Sub RightUp_MouseDown(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles RightUp.MouseDown
        sendData(22)
    End Sub

    Private Sub RightDown_MouseDown(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles RightDown.MouseDown
        sendData(21)
    End Sub

    Private Sub LeftUp_MouseDown(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles LeftUp.MouseDown
        sendData(24)
    End Sub

    Private Sub LeftDown_MouseDown(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles LeftDown.MouseDown
        sendData(23)
    End Sub

    Private Sub RightUp_MouseUp(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles RightUp.MouseUp
        sendData(20)
    End Sub

    Private Sub RightDown_MouseUp(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles RightDown.MouseUp
        sendData(20)
    End Sub

    Private Sub LeftUp_MouseUp(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles LeftUp.MouseUp
        sendData(20)
    End Sub

    Private Sub LeftDown_MouseUp(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles LeftDown.MouseUp
        sendData(20)
    End Sub

    Private Sub Form1_Load(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles MyBase.Load
        port = New SerialPort("COM1")
        port.BaudRate = 9600
        port.DataBits = 8

        portList = SerialPort.GetPortNames

        Dim s As String
        For Each s In portList
            PortsBox.Items.Add(s)
        Next s
        PortsBox.SelectedIndex = 0
        port.PortName = portList(PortsBox.SelectedIndex)
    End Sub

    Public Sub sendData(ByVal data As Integer)
        If port.IsOpen Then
            Try
                port.WriteLine(data.ToString)
            Catch ex As Exception
                ClosePort()
            End Try
        End If
    End Sub

    Private Sub ClosePort()
        Try
            port.DiscardInBuffer()
            port.DiscardOutBuffer()
            port.Close()
        Catch ex As Exception
            ' Do nothing
        End Try
    End Sub

    Private Sub Main_FormClosing(ByVal sender As Object, ByVal e As System.Windows.Forms.FormClosingEventArgs) Handles Me.FormClosing
        Try
            If port.IsOpen Then
                sendData(0)
            End If
            ClosePort()
        Catch ex As Exception
            ' Do nothing
        End Try
    End Sub

    Private Sub StepperSync_CheckedChanged(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles StepperSync.CheckedChanged
        If StepperSync.Checked Then
            sendData(11)
            RightUp.Enabled = False
            RightDown.Enabled = False
        Else
            sendData(10)
            RightUp.Enabled = True
            RightDown.Enabled = True
        End If
    End Sub

    Private Sub StepperEnable_CheckedChanged(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles StepperEnable.CheckedChanged
        If StepperEnable.Checked Then
            sendData(13)
        Else
            sendData(12)
        End If
    End Sub

    Private Sub PortsBox_SelectedIndexChanged(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles PortsBox.SelectedIndexChanged
        port.PortName = portList(PortsBox.SelectedIndex)
    End Sub

    Private Sub OpenPort_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles OpenPort.Click
        PortsBox.Enabled = False
        OpenPort.Enabled = False
        port.Open()
    End Sub

    '==================== Motor Buttons
    Private Sub NeckUp_MouseDown(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles NeckUp.MouseDown
        sendData(32)
    End Sub

    Private Sub NeckDown_MouseDown(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles NeckDown.MouseDown
        sendData(31)
    End Sub

    Private Sub HeadUp_MouseDown(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles HeadUp.MouseDown
        sendData(33)
    End Sub

    Private Sub HeadDown_MouseDown(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles HeadDown.MouseDown
        sendData(34)
    End Sub

    Private Sub NeckUp_MouseUp(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles NeckUp.MouseUp
        sendData(30)
    End Sub

    Private Sub NeckDown_MouseUp(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles NeckDown.MouseUp
        sendData(30)
    End Sub

    Private Sub HeadUp_MouseUp(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles HeadUp.MouseUp
        sendData(30)
    End Sub

    Private Sub HeadDown_MouseUp(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles HeadDown.MouseUp
        sendData(30)
    End Sub

    '==================== PWM labels and sliders
    Private Sub NeckSlider_MouseUp(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles NeckSlider.MouseUp
        sendData(14)
        sendData(NeckSlider.Value)
    End Sub

    Private Sub HeadSlider_MouseUp(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles HeadSlider.MouseUp
        sendData(15)
        sendData(HeadSlider.Value)
    End Sub

    Private Sub HeadSlider_Scroll(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles HeadSlider.Scroll
        HeadLabel.Text = HeadSlider.Value
    End Sub

    Private Sub NeckSlider_Scroll(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles NeckSlider.Scroll
        NeckLabel.Text = NeckSlider.Value
    End Sub


End Class
