using System;
using System.Drawing;
using System.Collections;
using System.Windows.Forms;
using System.Data;
using System.Runtime.InteropServices;

namespace EgumaCppLibTester
{
	public class Form1 : System.Windows.Forms.Form
	{
	
		[DllImport("Eguma.dll")]
		public static extern bool GetBalance(string apiKey, string code, char[] codeOut, ref bool isRedeemable, ref Int32 balanceInCents, ref Int32 totalAmountInCents, char[] messageOut, char[] error);

		[DllImport("Eguma.dll")]
		public static extern bool Hello();


		private System.Windows.Forms.Button button2;
		private System.Windows.Forms.Label labelCodeOut;
		private System.Windows.Forms.Label label1;
		private System.Windows.Forms.Label label2;
		private System.Windows.Forms.Label label4;
		private System.Windows.Forms.Label labelIsRedeemable;
		private System.Windows.Forms.Label labelBalance;
		private System.Windows.Forms.Label labelMessage;
		private System.Windows.Forms.Label label6;
		private System.Windows.Forms.Label labelTotalAmount;
		private System.Windows.Forms.Label labelXX;
		private System.Windows.Forms.Button button3;



		private System.Windows.Forms.Button button1;
	
		public Form1()
		{
			//
			// Required for Windows Form Designer support
			//
			InitializeComponent();

			//
			// TODO: Add any constructor code after InitializeComponent call
			//
		}
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		protected override void Dispose( bool disposing )
		{
			base.Dispose( disposing );
		}
		#region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		private void InitializeComponent()
		{
			this.button1 = new System.Windows.Forms.Button();
			this.button2 = new System.Windows.Forms.Button();
			this.labelCodeOut = new System.Windows.Forms.Label();
			this.label1 = new System.Windows.Forms.Label();
			this.label2 = new System.Windows.Forms.Label();
			this.label4 = new System.Windows.Forms.Label();
			this.labelIsRedeemable = new System.Windows.Forms.Label();
			this.labelBalance = new System.Windows.Forms.Label();
			this.labelTotalAmount = new System.Windows.Forms.Label();
			this.labelXX = new System.Windows.Forms.Label();
			this.labelMessage = new System.Windows.Forms.Label();
			this.label6 = new System.Windows.Forms.Label();
			this.button3 = new System.Windows.Forms.Button();
			// 
			// button1
			// 
			this.button1.Location = new System.Drawing.Point(64, 40);
			this.button1.Size = new System.Drawing.Size(200, 56);
			this.button1.Text = "Check Balance";
			this.button1.Click += new System.EventHandler(this.button1_Click);
			// 
			// button2
			// 
			this.button2.Location = new System.Drawing.Point(128, 280);
			this.button2.Size = new System.Drawing.Size(200, 80);
			this.button2.Text = "Close";
			this.button2.Click += new System.EventHandler(this.button2_Click);
			// 
			// labelCodeOut
			// 
			this.labelCodeOut.Location = new System.Drawing.Point(152, 136);
			// 
			// label1
			// 
			this.label1.Location = new System.Drawing.Point(52, 136);
			this.label1.Text = "Code Out:";
			this.label1.TextAlign = System.Drawing.ContentAlignment.TopRight;
			// 
			// label2
			// 
			this.label2.Location = new System.Drawing.Point(-24, 160);
			this.label2.Size = new System.Drawing.Size(176, 24);
			this.label2.Text = "Balance (in Cents):";
			this.label2.TextAlign = System.Drawing.ContentAlignment.TopRight;
			// 
			// label4
			// 
			this.label4.Location = new System.Drawing.Point(-24, 112);
			this.label4.Size = new System.Drawing.Size(176, 24);
			this.label4.Text = "Is Redeemable:";
			this.label4.TextAlign = System.Drawing.ContentAlignment.TopRight;
			// 
			// labelIsRedeemable
			// 
			this.labelIsRedeemable.Location = new System.Drawing.Point(152, 112);
			// 
			// labelBalance
			// 
			this.labelBalance.Location = new System.Drawing.Point(152, 160);
			// 
			// labelTotalAmount
			// 
			this.labelTotalAmount.Location = new System.Drawing.Point(152, 184);
			// 
			// labelXX
			// 
			this.labelXX.Location = new System.Drawing.Point(-24, 184);
			this.labelXX.Size = new System.Drawing.Size(176, 24);
			this.labelXX.Text = "Total Amount (in Cents):";
			this.labelXX.TextAlign = System.Drawing.ContentAlignment.TopRight;
			// 
			// labelMessage
			// 
			this.labelMessage.Location = new System.Drawing.Point(152, 208);
			this.labelMessage.Size = new System.Drawing.Size(392, 20);
			// 
			// label6
			// 
			this.label6.Location = new System.Drawing.Point(-24, 208);
			this.label6.Size = new System.Drawing.Size(176, 24);
			this.label6.Text = "Message:";
			this.label6.TextAlign = System.Drawing.ContentAlignment.TopRight;
			// 
			// button3
			// 
			this.button3.Location = new System.Drawing.Point(320, 40);
			this.button3.Size = new System.Drawing.Size(144, 56);
			this.button3.Text = "Hello";
			this.button3.Click += new System.EventHandler(this.button3_Click);
			// 
			// Form1
			// 
			this.Controls.Add(this.button3);
			this.Controls.Add(this.labelMessage);
			this.Controls.Add(this.label6);
			this.Controls.Add(this.labelTotalAmount);
			this.Controls.Add(this.labelXX);
			this.Controls.Add(this.labelBalance);
			this.Controls.Add(this.label4);
			this.Controls.Add(this.labelIsRedeemable);
			this.Controls.Add(this.label2);
			this.Controls.Add(this.label1);
			this.Controls.Add(this.labelCodeOut);
			this.Controls.Add(this.button2);
			this.Controls.Add(this.button1);
			this.Text = "E-GUMA Win CE Tester";

		}
		#endregion

		/// <summary>
		/// The main entry point for the application.
		/// </summary>

		static void Main() 
		{
			Application.Run(new Form1());
		}

		private void button1_Click(object sender, System.EventArgs e)
		{
			int balanceInCents = 1;
			int totalAmount = 0;
			char[] codeOut = new char[32];
			char [] message = new char[1024];
			char[] error = new char[1024];
			bool isRedeemable = false;

			GetBalance("510e32c594d84816a4af9df0", "2QH3-QTDM-28N6", codeOut, ref isRedeemable, ref balanceInCents, ref totalAmount, message, error);

			labelIsRedeemable.Text = isRedeemable ? "true" : "false";
			labelCodeOut.Text = new String(codeOut);
			labelBalance.Text = balanceInCents.ToString();
			labelTotalAmount.Text = totalAmount.ToString();
			labelMessage.Text = new string(message);
		}

		private void button2_Click(object sender, System.EventArgs e)
		{
			Close();
		}

		private void button3_Click(object sender, System.EventArgs e)
		{
			if (Hello())
				MessageBox.Show("OK");
			else
				MessageBox.Show("something went wrong...");
		}
	}
}
