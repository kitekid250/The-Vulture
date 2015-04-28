<Global.Microsoft.VisualBasic.CompilerServices.DesignerGenerated()> _
Partial Class Main
    Inherits System.Windows.Forms.Form

    'Form overrides dispose to clean up the component list.
    <System.Diagnostics.DebuggerNonUserCode()> _
    Protected Overrides Sub Dispose(ByVal disposing As Boolean)
        Try
            If disposing AndAlso components IsNot Nothing Then
                components.Dispose()
            End If
        Finally
            MyBase.Dispose(disposing)
        End Try
    End Sub

    'Required by the Windows Form Designer
    Private components As System.ComponentModel.IContainer

    'NOTE: The following procedure is required by the Windows Form Designer
    'It can be modified using the Windows Form Designer.  
    'Do not modify it using the code editor.
    <System.Diagnostics.DebuggerStepThrough()> _
    Private Sub InitializeComponent()
        Dim resources As System.ComponentModel.ComponentResourceManager = New System.ComponentModel.ComponentResourceManager(GetType(Main))
        Me.LeftUp = New System.Windows.Forms.Button()
        Me.LeftDown = New System.Windows.Forms.Button()
        Me.RightUp = New System.Windows.Forms.Button()
        Me.RightDown = New System.Windows.Forms.Button()
        Me.NeckUp = New System.Windows.Forms.Button()
        Me.NeckDown = New System.Windows.Forms.Button()
        Me.HeadUp = New System.Windows.Forms.Button()
        Me.HeadDown = New System.Windows.Forms.Button()
        Me.NeckSlider = New System.Windows.Forms.TrackBar()
        Me.HeadSlider = New System.Windows.Forms.TrackBar()
        Me.StepperSync = New System.Windows.Forms.CheckBox()
        Me.StepperEnable = New System.Windows.Forms.CheckBox()
        Me.NeckLabel = New System.Windows.Forms.Label()
        Me.HeadLabel = New System.Windows.Forms.Label()
        Me.Label3 = New System.Windows.Forms.Label()
        Me.Label4 = New System.Windows.Forms.Label()
        Me.Label5 = New System.Windows.Forms.Label()
        Me.Label6 = New System.Windows.Forms.Label()
        Me.OpenPort = New System.Windows.Forms.Button()
        Me.PortsBox = New System.Windows.Forms.ComboBox()
        CType(Me.NeckSlider, System.ComponentModel.ISupportInitialize).BeginInit()
        CType(Me.HeadSlider, System.ComponentModel.ISupportInitialize).BeginInit()
        Me.SuspendLayout()
        '
        'LeftUp
        '
        Me.LeftUp.Location = New System.Drawing.Point(22, 26)
        Me.LeftUp.Name = "LeftUp"
        Me.LeftUp.Size = New System.Drawing.Size(75, 23)
        Me.LeftUp.TabIndex = 0
        Me.LeftUp.Text = "Up"
        Me.LeftUp.UseVisualStyleBackColor = True
        '
        'LeftDown
        '
        Me.LeftDown.Location = New System.Drawing.Point(22, 97)
        Me.LeftDown.Name = "LeftDown"
        Me.LeftDown.Size = New System.Drawing.Size(75, 23)
        Me.LeftDown.TabIndex = 1
        Me.LeftDown.Text = "Down"
        Me.LeftDown.UseVisualStyleBackColor = True
        '
        'RightUp
        '
        Me.RightUp.Location = New System.Drawing.Point(156, 26)
        Me.RightUp.Name = "RightUp"
        Me.RightUp.Size = New System.Drawing.Size(75, 23)
        Me.RightUp.TabIndex = 2
        Me.RightUp.Text = "Up"
        Me.RightUp.UseVisualStyleBackColor = True
        '
        'RightDown
        '
        Me.RightDown.Location = New System.Drawing.Point(156, 97)
        Me.RightDown.Name = "RightDown"
        Me.RightDown.Size = New System.Drawing.Size(75, 23)
        Me.RightDown.TabIndex = 3
        Me.RightDown.Text = "Down"
        Me.RightDown.UseVisualStyleBackColor = True
        '
        'NeckUp
        '
        Me.NeckUp.Location = New System.Drawing.Point(326, 26)
        Me.NeckUp.Name = "NeckUp"
        Me.NeckUp.Size = New System.Drawing.Size(75, 23)
        Me.NeckUp.TabIndex = 4
        Me.NeckUp.Text = "Up"
        Me.NeckUp.UseVisualStyleBackColor = True
        '
        'NeckDown
        '
        Me.NeckDown.Location = New System.Drawing.Point(326, 97)
        Me.NeckDown.Name = "NeckDown"
        Me.NeckDown.Size = New System.Drawing.Size(75, 23)
        Me.NeckDown.TabIndex = 5
        Me.NeckDown.Text = "Down"
        Me.NeckDown.UseVisualStyleBackColor = True
        '
        'HeadUp
        '
        Me.HeadUp.Location = New System.Drawing.Point(493, 26)
        Me.HeadUp.Name = "HeadUp"
        Me.HeadUp.Size = New System.Drawing.Size(75, 23)
        Me.HeadUp.TabIndex = 7
        Me.HeadUp.Text = "Up"
        Me.HeadUp.UseVisualStyleBackColor = True
        '
        'HeadDown
        '
        Me.HeadDown.Location = New System.Drawing.Point(493, 97)
        Me.HeadDown.Name = "HeadDown"
        Me.HeadDown.Size = New System.Drawing.Size(75, 23)
        Me.HeadDown.TabIndex = 8
        Me.HeadDown.Text = "Down"
        Me.HeadDown.UseVisualStyleBackColor = True
        '
        'NeckSlider
        '
        Me.NeckSlider.Location = New System.Drawing.Point(275, 26)
        Me.NeckSlider.Maximum = 255
        Me.NeckSlider.Name = "NeckSlider"
        Me.NeckSlider.Orientation = System.Windows.Forms.Orientation.Vertical
        Me.NeckSlider.Size = New System.Drawing.Size(45, 104)
        Me.NeckSlider.TabIndex = 9
        Me.NeckSlider.TickStyle = System.Windows.Forms.TickStyle.None
        '
        'HeadSlider
        '
        Me.HeadSlider.Location = New System.Drawing.Point(442, 26)
        Me.HeadSlider.Maximum = 255
        Me.HeadSlider.Name = "HeadSlider"
        Me.HeadSlider.Orientation = System.Windows.Forms.Orientation.Vertical
        Me.HeadSlider.Size = New System.Drawing.Size(45, 104)
        Me.HeadSlider.TabIndex = 10
        Me.HeadSlider.TickStyle = System.Windows.Forms.TickStyle.None
        '
        'StepperSync
        '
        Me.StepperSync.AutoSize = True
        Me.StepperSync.Location = New System.Drawing.Point(16, 126)
        Me.StepperSync.Name = "StepperSync"
        Me.StepperSync.Size = New System.Drawing.Size(95, 17)
        Me.StepperSync.TabIndex = 11
        Me.StepperSync.Text = "Sync Steppers"
        Me.StepperSync.UseVisualStyleBackColor = True
        '
        'StepperEnable
        '
        Me.StepperEnable.AutoSize = True
        Me.StepperEnable.Location = New System.Drawing.Point(150, 126)
        Me.StepperEnable.Name = "StepperEnable"
        Me.StepperEnable.Size = New System.Drawing.Size(104, 17)
        Me.StepperEnable.TabIndex = 12
        Me.StepperEnable.Text = "Enable Steppers"
        Me.StepperEnable.UseVisualStyleBackColor = True
        '
        'NeckLabel
        '
        Me.NeckLabel.AutoSize = True
        Me.NeckLabel.Location = New System.Drawing.Point(272, 130)
        Me.NeckLabel.Name = "NeckLabel"
        Me.NeckLabel.Size = New System.Drawing.Size(13, 13)
        Me.NeckLabel.TabIndex = 13
        Me.NeckLabel.Text = "0"
        '
        'HeadLabel
        '
        Me.HeadLabel.AutoSize = True
        Me.HeadLabel.Location = New System.Drawing.Point(439, 130)
        Me.HeadLabel.Name = "HeadLabel"
        Me.HeadLabel.Size = New System.Drawing.Size(13, 13)
        Me.HeadLabel.TabIndex = 14
        Me.HeadLabel.Text = "0"
        '
        'Label3
        '
        Me.Label3.AutoSize = True
        Me.Label3.Location = New System.Drawing.Point(19, 67)
        Me.Label3.Name = "Label3"
        Me.Label3.Size = New System.Drawing.Size(53, 13)
        Me.Label3.TabIndex = 15
        Me.Label3.Text = "Left Wing"
        '
        'Label4
        '
        Me.Label4.AutoSize = True
        Me.Label4.Location = New System.Drawing.Point(153, 67)
        Me.Label4.Name = "Label4"
        Me.Label4.Size = New System.Drawing.Size(60, 13)
        Me.Label4.TabIndex = 16
        Me.Label4.Text = "Right Wing"
        '
        'Label5
        '
        Me.Label5.AutoSize = True
        Me.Label5.Location = New System.Drawing.Point(323, 67)
        Me.Label5.Name = "Label5"
        Me.Label5.Size = New System.Drawing.Size(73, 13)
        Me.Label5.TabIndex = 17
        Me.Label5.Text = "Wing Controls"
        '
        'Label6
        '
        Me.Label6.AutoSize = True
        Me.Label6.Location = New System.Drawing.Point(490, 67)
        Me.Label6.Name = "Label6"
        Me.Label6.Size = New System.Drawing.Size(74, 13)
        Me.Label6.TabIndex = 18
        Me.Label6.Text = "Neck Controls"
        '
        'OpenPort
        '
        Me.OpenPort.Location = New System.Drawing.Point(211, 170)
        Me.OpenPort.Name = "OpenPort"
        Me.OpenPort.Size = New System.Drawing.Size(75, 23)
        Me.OpenPort.TabIndex = 19
        Me.OpenPort.Text = "Open Port"
        Me.OpenPort.UseVisualStyleBackColor = True
        '
        'PortsBox
        '
        Me.PortsBox.FormattingEnabled = True
        Me.PortsBox.Location = New System.Drawing.Point(292, 170)
        Me.PortsBox.Name = "PortsBox"
        Me.PortsBox.Size = New System.Drawing.Size(121, 21)
        Me.PortsBox.TabIndex = 20
        '
        'Main
        '
        Me.AutoScaleDimensions = New System.Drawing.SizeF(6.0!, 13.0!)
        Me.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font
        Me.BackColor = System.Drawing.SystemColors.Control
        Me.ClientSize = New System.Drawing.Size(614, 230)
        Me.Controls.Add(Me.PortsBox)
        Me.Controls.Add(Me.OpenPort)
        Me.Controls.Add(Me.Label6)
        Me.Controls.Add(Me.Label5)
        Me.Controls.Add(Me.Label4)
        Me.Controls.Add(Me.Label3)
        Me.Controls.Add(Me.HeadLabel)
        Me.Controls.Add(Me.NeckLabel)
        Me.Controls.Add(Me.StepperEnable)
        Me.Controls.Add(Me.StepperSync)
        Me.Controls.Add(Me.HeadSlider)
        Me.Controls.Add(Me.NeckSlider)
        Me.Controls.Add(Me.HeadDown)
        Me.Controls.Add(Me.HeadUp)
        Me.Controls.Add(Me.NeckDown)
        Me.Controls.Add(Me.NeckUp)
        Me.Controls.Add(Me.RightDown)
        Me.Controls.Add(Me.RightUp)
        Me.Controls.Add(Me.LeftDown)
        Me.Controls.Add(Me.LeftUp)
        Me.Icon = CType(resources.GetObject("$this.Icon"), System.Drawing.Icon)
        Me.Name = "Main"
        Me.Text = "Vulture Jogger Program"
        CType(Me.NeckSlider, System.ComponentModel.ISupportInitialize).EndInit()
        CType(Me.HeadSlider, System.ComponentModel.ISupportInitialize).EndInit()
        Me.ResumeLayout(False)
        Me.PerformLayout()

    End Sub
    Friend WithEvents LeftUp As System.Windows.Forms.Button
    Friend WithEvents LeftDown As System.Windows.Forms.Button
    Friend WithEvents RightUp As System.Windows.Forms.Button
    Friend WithEvents RightDown As System.Windows.Forms.Button
    Friend WithEvents NeckUp As System.Windows.Forms.Button
    Friend WithEvents NeckDown As System.Windows.Forms.Button
    Friend WithEvents HeadUp As System.Windows.Forms.Button
    Friend WithEvents HeadDown As System.Windows.Forms.Button
    Friend WithEvents NeckSlider As System.Windows.Forms.TrackBar
    Friend WithEvents HeadSlider As System.Windows.Forms.TrackBar
    Friend WithEvents StepperSync As System.Windows.Forms.CheckBox
    Friend WithEvents StepperEnable As System.Windows.Forms.CheckBox
    Friend WithEvents NeckLabel As System.Windows.Forms.Label
    Friend WithEvents HeadLabel As System.Windows.Forms.Label
    Friend WithEvents Label3 As System.Windows.Forms.Label
    Friend WithEvents Label4 As System.Windows.Forms.Label
    Friend WithEvents Label5 As System.Windows.Forms.Label
    Friend WithEvents Label6 As System.Windows.Forms.Label
    Friend WithEvents OpenPort As System.Windows.Forms.Button
    Friend WithEvents PortsBox As System.Windows.Forms.ComboBox
End Class
