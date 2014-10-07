object Form1: TForm1
  Left = 119
  Top = 252
  Width = 1028
  Height = 463
  Caption = 'OGG Decoding/Encoding'
  Color = clMedGray
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object GroupBox1: TGroupBox
    Left = 8
    Top = 8
    Width = 481
    Height = 401
    Caption = #1044#1077#1082#1086#1076#1080#1088#1086#1074#1072#1085#1080#1077' .ogg '#1092#1072#1081#1083#1072
    TabOrder = 0
    object Label6: TLabel
      Left = 16
      Top = 360
      Width = 81
      Height = 13
      Caption = #1054#1090#1082#1088#1099#1090#1099#1081' '#1092#1072#1081#1083
    end
    object GroupBox2: TGroupBox
      Left = 16
      Top = 16
      Width = 457
      Height = 113
      Caption = #1057#1074#1086#1081#1089#1090#1074#1072' '#1092#1072#1081#1083#1072
      TabOrder = 0
      object LabeledEdit1: TLabeledEdit
        Left = 16
        Top = 32
        Width = 113
        Height = 21
        EditLabel.Width = 77
        EditLabel.Height = 13
        EditLabel.Caption = #1063#1080#1089#1083#1086' '#1082#1072#1085#1072#1083#1086#1074
        LabelPosition = lpAbove
        LabelSpacing = 3
        ReadOnly = True
        TabOrder = 0
      end
      object LabeledEdit2: TLabeledEdit
        Left = 136
        Top = 32
        Width = 113
        Height = 21
        EditLabel.Width = 122
        EditLabel.Height = 13
        EditLabel.Caption = #1063#1072#1089#1090#1086#1090#1072' '#1076#1080#1089#1082#1088#1077#1090#1080#1079#1072#1094#1080#1080
        LabelPosition = lpAbove
        LabelSpacing = 3
        ReadOnly = True
        TabOrder = 1
      end
      object LabeledEdit3: TLabeledEdit
        Left = 280
        Top = 32
        Width = 113
        Height = 21
        EditLabel.Width = 170
        EditLabel.Height = 13
        EditLabel.Caption = #1056#1072#1079#1084#1077#1088#1099' '#1073#1083#1086#1082#1086' '#1076#1083#1103' '#1082#1086#1076#1080#1088#1086#1074#1072#1085#1080#1103
        LabelPosition = lpAbove
        LabelSpacing = 3
        TabOrder = 2
      end
      object LabeledEdit4: TLabeledEdit
        Left = 16
        Top = 80
        Width = 377
        Height = 21
        EditLabel.Width = 180
        EditLabel.Height = 13
        EditLabel.Caption = #1053#1072#1079#1074#1072#1085#1080#1077' '#1089#1086#1092#1090#1072', '#1089#1086#1079#1076#1072#1074#1096#1077#1075#1086' '#1092#1072#1081#1083
        LabelPosition = lpAbove
        LabelSpacing = 3
        TabOrder = 3
      end
    end
    object GroupBox3: TGroupBox
      Left = 16
      Top = 136
      Width = 457
      Height = 193
      Caption = #1050#1086#1084#1084#1077#1085#1090#1072#1088#1080#1080
      TabOrder = 1
      object ListBox1: TListBox
        Left = 16
        Top = 24
        Width = 113
        Height = 153
        ItemHeight = 13
        TabOrder = 0
        OnClick = ListBox1Click
      end
      object RichEdit1: TRichEdit
        Left = 144
        Top = 24
        Width = 297
        Height = 153
        Lines.Strings = (
          '')
        ScrollBars = ssVertical
        TabOrder = 1
      end
    end
    object Button1: TButton
      Left = 184
      Top = 336
      Width = 137
      Height = 25
      Caption = #1044#1077#1082#1086#1076#1080#1088#1086#1074#1072#1090#1100
      TabOrder = 3
      OnClick = Button1Click
    end
    object Button2: TButton
      Left = 40
      Top = 336
      Width = 105
      Height = 25
      Caption = #1054#1090#1082#1088#1099#1090#1100
      TabOrder = 2
      OnClick = Button2Click
    end
    object Edit1: TEdit
      Left = 16
      Top = 376
      Width = 449
      Height = 21
      TabOrder = 4
    end
  end
  object GroupBox4: TGroupBox
    Left = 488
    Top = 8
    Width = 521
    Height = 401
    Caption = #1047#1072#1087#1080#1089#1100' '#1085#1086#1074#1086#1075#1086' '#1092#1072#1081#1083#1072
    TabOrder = 1
    object Label2: TLabel
      Left = 16
      Top = 96
      Width = 47
      Height = 13
      Caption = #1050#1072#1095#1077#1089#1090#1074#1086
    end
    object Label3: TLabel
      Left = 8
      Top = 144
      Width = 37
      Height = 13
      Caption = #1055#1083#1086#1093#1086#1077
    end
    object Label4: TLabel
      Left = 216
      Top = 144
      Width = 43
      Height = 13
      Caption = #1057#1088#1077#1076#1085#1077#1077
    end
    object Label5: TLabel
      Left = 464
      Top = 144
      Width = 45
      Height = 13
      Caption = #1061#1086#1088#1086#1096#1077#1077
    end
    object LabeledEdit5: TLabeledEdit
      Left = 16
      Top = 32
      Width = 401
      Height = 21
      EditLabel.Width = 61
      EditLabel.Height = 13
      EditLabel.Caption = #1060#1072#1081#1083' *WAV'
      LabelPosition = lpAbove
      LabelSpacing = 3
      ReadOnly = True
      TabOrder = 0
    end
    object Button3: TButton
      Left = 32
      Top = 64
      Width = 105
      Height = 25
      Caption = #1054#1090#1082#1088#1099#1090#1100
      TabOrder = 1
      OnClick = Button3Click
    end
    object Button4: TButton
      Left = 368
      Top = 64
      Width = 137
      Height = 25
      Caption = #1050#1086#1076#1080#1088#1086#1074#1072#1090#1100
      TabOrder = 3
      OnClick = Button4Click
    end
    object GroupBox5: TGroupBox
      Left = 16
      Top = 160
      Width = 497
      Height = 225
      Caption = #1050#1086#1084#1084#1077#1085#1090#1072#1088#1080#1080
      TabOrder = 5
      object Label1: TLabel
        Left = 16
        Top = 64
        Width = 108
        Height = 13
        Caption = #1057#1086#1076#1077#1088#1078#1072#1085#1080#1077' '#1088#1072#1079#1076#1077#1083#1072
      end
      object LabeledEdit6: TLabeledEdit
        Left = 16
        Top = 40
        Width = 473
        Height = 21
        EditLabel.Width = 167
        EditLabel.Height = 13
        EditLabel.Caption = #1053#1072#1079#1074#1072#1085#1080#1077' '#1088#1072#1079#1076#1077#1083#1072' '#1082#1086#1084#1084#1077#1085#1090#1072#1088#1080#1103
        LabelPosition = lpAbove
        LabelSpacing = 3
        TabOrder = 0
      end
      object RichEdit2: TRichEdit
        Left = 16
        Top = 80
        Width = 473
        Height = 137
        TabOrder = 1
      end
    end
    object Button5: TButton
      Left = 168
      Top = 64
      Width = 169
      Height = 25
      Caption = #1044#1086#1073#1072#1074#1080#1090#1100' '#1082#1086#1084#1084#1077#1085#1090#1072#1088#1080#1081
      TabOrder = 2
      OnClick = Button5Click
    end
    object TrackBar1: TTrackBar
      Left = 16
      Top = 112
      Width = 489
      Height = 25
      Max = 9
      Orientation = trHorizontal
      Frequency = 1
      Position = 4
      SelEnd = 0
      SelStart = 0
      TabOrder = 4
      TickMarks = tmBottomRight
      TickStyle = tsAuto
    end
  end
  object ProgressBar1: TProgressBar
    Left = 8
    Top = 408
    Width = 1001
    Height = 18
    Min = 0
    Max = 100
    TabOrder = 2
  end
  object OpenDialog1: TOpenDialog
    Filter = 'Ogg '#1092#1086#1088#1084#1072#1090'|*.ogg'
    Left = 344
    Top = 8
  end
  object SaveDialog1: TSaveDialog
    DefaultExt = '.pcm'
    Filter = 'pcm|*.pcm'
    Left = 400
    Top = 8
  end
  object OpenDialog2: TOpenDialog
    Filter = 'WAV|*.WAV'
    Left = 56
    Top = 208
  end
  object SaveDialog2: TSaveDialog
    DefaultExt = '.ogg'
    Filter = 'ogg|*.ogg'
    Left = 88
    Top = 208
  end
end
